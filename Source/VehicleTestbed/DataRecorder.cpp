#include "DataRecorder.h"


DataPoint& DataRecorder::Pop()
{
	std::unique_lock<std::mutex> mlock(Mutex);
	while (Queue.empty())
	{
		Cond.wait(mlock);
	}
	DataPoint& item = Queue.front();
	Queue.pop();
	return item;
}

void DataRecorder::Pop(DataPoint& item)
{
	std::unique_lock<std::mutex> mlock(Mutex);
	while (Queue.empty())
	{
		Cond.wait(mlock);
	}
	item = Queue.front();
	Queue.pop();
}

void DataRecorder::Push(const DataPoint& item)
{
	std::unique_lock<std::mutex> mlock(Mutex);
	Queue.push(item);
	mlock.unlock();
	Cond.notify_one();
}

void DataRecorder::Push(DataPoint&& item)
{
	std::unique_lock<std::mutex> mlock(Mutex);
	Queue.push(std::move(item));
	mlock.unlock();
	Cond.notify_one();
}

DataRecorder::DataRecorder() : ClockRateMS(100) { }

DataRecorder::DataRecorder(int clockRateMS) : ClockRateMS(clockRateMS) { }

DataRecorder::DataRecorder(int clockRateMS, std::vector<const void*> collectors) : ClockRateMS(clockRateMS) { }


void DataRecorder::ReadFromCollectors()
{
	do {
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::milliseconds milliseconds;
		Clock::time_point t0 = Clock::now();

		DataPoint dataPoint;
		for (std::vector<const void*>::const_iterator iter = Collectors.begin(), end = Collectors.end(); iter != end; ++iter)
		{
			DataValue value(*iter);
			dataPoint.AddData(&value);
		}
		Push(dataPoint);

		Clock::time_point t1 = Clock::now();
		milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10 - ms.count()));
	} while (!bStop);
}


std::thread DataRecorder::StartWriter()
{
	return std::thread([=] { WriteToFile(); });;
}

std::thread DataRecorder::StartReader()
{
	return std::thread([=] { ReadFromCollectors(); });
}

void DataRecorder::WriteToFile()
{
	std::fstream fs;
	fs.open("test.txt", std::fstream::out | std::fstream::ate);
	do {
		auto dataPoint = Pop();
		if (dataPoint != DataPoint::NIL)
		{
			fs << dataPoint << std::endl;
		}
	} while (!bStop);

	fs.close();
}

void DataRecorder::SetClockRate(int clockRateMS)
{
	ClockRateMS = clockRateMS;
}

int DataRecorder::GetClockRate()
{
	return ClockRateMS;
}

void DataRecorder::AddCollector(const void* collector)
{
	Collectors.push_back(collector);
}

void DataRecorder::AddCollectors(std::vector<const void*> collectors)
{
	Collectors.insert(Collectors.end(), collectors.begin(), collectors.end());
}

void DataRecorder::Start()
{
	ReaderThread = StartReader();
	WriterThread = StartWriter();
}

void DataRecorder::Stop()
{
	bStop = true;
	Push(DataPoint::NIL);
	Cond.notify_all();

	ReaderThread.join();
	WriterThread.join();
}
