#include "DataRecorder.h"

bool DataRecorder::Pop(DataPoint& item)
{
	std::lock_guard<std::mutex> mlock(Mutex);
	if (Queue.empty())
	{
		return false;
	}
	item = *Queue.front();
	Queue.pop();
	return true;
}

void DataRecorder::Push(DataPoint* item)
{
	std::lock_guard<std::mutex> mlock(Mutex);
	Queue.push(std::move(item));
	Cond.notify_one();
}

DataRecorder::DataRecorder() : ClockRateMS(100) { }

DataRecorder::DataRecorder(int clockRateMS) : ClockRateMS(clockRateMS) { }

DataRecorder::DataRecorder(int clockRateMS, std::vector<std::pair<const void*, DataType>> collectors) : ClockRateMS(clockRateMS), Collectors(collectors) { }

void DataRecorder::ReadFromCollectors()
{
	do {
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::milliseconds milliseconds;
		Clock::time_point t0 = Clock::now();

		DataPoint dataPoint;
		for (unsigned int i = 0; i < Collectors.size(); i++)
		{
			switch (Collectors[i].second)
			{
			case DataType::BOOL:
			{
				bool temp = *(bool *)Collectors[i].first;
				DataValue<bool> value(temp);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT:
			{
				int temp = *(int *)Collectors[i].first;
				DataValue<int> value(temp);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT:
			{
				DataValue<unsigned int> value(*(unsigned int*)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::DOUBLE:
			{
				DataValue<double> value(*(double *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::STRING:
			{
				DataValue<std::string> value(*(std::string *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			}
		}
		Push(&dataPoint);

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
		DataPoint writeDataPoint;
		if (Pop(writeDataPoint))
		{
			fs << writeDataPoint << std::endl;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(ClockRateMS));
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

void DataRecorder::AddCollector(const void* ptr, DataType type)
{
	Collectors.push_back(std::pair<const void*, DataType>(ptr, type));
}

void DataRecorder::AddCollectors(std::vector<std::pair<const void*, DataType>> collectors)
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
	Cond.notify_all();

	ReaderThread.join();
	WriterThread.join();
}
