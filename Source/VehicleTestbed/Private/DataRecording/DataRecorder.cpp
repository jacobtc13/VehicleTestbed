#include "DataRecorder.h"

bool UDataRecorder::Pop(std::unique_ptr<DataPoint>& item)
{
	std::lock_guard<std::mutex> mlock(Mutex); // released when mlock goes out of scope
	if (Queue.empty())
	{
		return false;
	}
	item = std::move(Queue.front());
	Queue.pop();
	return true;
}

void UDataRecorder::Push(std::unique_ptr<DataPoint> item)
{
	std::lock_guard<std::mutex> mlock(Mutex); // released when mlock goes out of scope
	Queue.push(std::move(item));
	Cond.notify_one();
}

UDataRecorder::UDataRecorder() : ClockRateMS(100), Filename("data.csv") { }

UDataRecorder::UDataRecorder(int clockRateMS) : ClockRateMS(clockRateMS), Filename("data.csv") { }

UDataRecorder::UDataRecorder(std::string filename) : ClockRateMS(100), Filename(filename) { }

UDataRecorder::UDataRecorder(int clockRateMS, std::string filename) 
	: ClockRateMS(clockRateMS), Filename(filename) { }

UDataRecorder::~UDataRecorder()
{
	for (unsigned int i = 0; i < Collectors.size(); i++)
	{
		delete Collectors[i];
	}
	std::lock_guard<std::mutex> mlock(Mutex);
	while (!Queue.empty()) 
	{
		Queue.pop();
	}
}

void UDataRecorder::BeginDestroy()
{
	UObject::BeginDestroy();
	if (!bStop)
	{
		Stop();
	}
}

void UDataRecorder::ReadFromCollectors()
{
	do {
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::milliseconds milliseconds;
		Clock::time_point t0 = Clock::now();

		std::unique_ptr<DataPoint> dataPoint = std::make_unique<DataPoint>();

		for (unsigned int i = 0; i < Collectors.size(); i++)
		{
			if (Collectors[i]->IsEnabled())
			{
				dataPoint->AddData(std::move(Collectors[i]->Collect()));
			}
		}
		Push(std::move(dataPoint));

		// Wait remaining time until next tick
		Clock::time_point t1 = Clock::now();
		milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10 - ms.count()));

		// Wait thread while paused
		std::unique_lock<std::mutex> mlock(Mutex);
		while (bPause)
		{
			Cond.wait(mlock);
		}
		mlock.unlock();

	} while (!bStop);
}

void UDataRecorder::WriteToFile()
{
	std::fstream fs;
	FString path = FPaths::ProjectDir();
	std::string filepath = std::string(TCHAR_TO_UTF8(*path));
	fs.open(filepath+Filename, std::fstream::out | std::fstream::ate);

	// Print header row
	fs << "Timestamp,";
	for (unsigned int i = 0; i < Collectors.size(); i++)
	{
		if (Collectors[i]->IsEnabled())
		{
			fs << std::string(TCHAR_TO_UTF8(*Collectors[i]->GetName().ToString())) << ',';
		}
	}
	fs << std::endl;

	// Print datapoints until stop is set
	do {
		std::unique_ptr<DataPoint> writeDataPoint;
		// Write datapoints until list is empty
		while (Pop(writeDataPoint))
		{
			fs << *writeDataPoint << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(ClockRateMS));
	} while (!bStop);

	fs.close();
}

std::thread UDataRecorder::StartWriter()
{
	return std::thread([=] { WriteToFile(); });;
}

std::thread UDataRecorder::StartReader()
{
	return std::thread([=] { ReadFromCollectors(); });
}

void UDataRecorder::SetClockRate(int clockRateMS)
{
	ClockRateMS = clockRateMS;
}

int UDataRecorder::GetClockRate()
{
	return ClockRateMS;
}

void UDataRecorder::AddCollector(DataCollectorBase* collector)
{
	Collectors.push_back(collector);
}

void UDataRecorder::Start()
{
	// Spawn threads if not already runnning
	if(!ReaderThread.joinable()) ReaderThread = StartReader();
	if(!WriterThread.joinable()) WriterThread = StartWriter();
	bStop = false;
	bPause = false;
}

void UDataRecorder::Stop()
{
	bPause = false;
	bStop = true;
	Cond.notify_all();

	if (ReaderThread.joinable()) ReaderThread.join();
	if (WriterThread.joinable()) WriterThread.join();
}

void UDataRecorder::Pause()
{
	bPause = true;
}

void UDataRecorder::Resume()
{
	bPause = false;
	Cond.notify_one();
}
