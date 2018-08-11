#include "DataRecorder.h"

bool UDataRecorder::Pop(DataPoint& item)
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

void UDataRecorder::Push(DataPoint* item)
{
	std::lock_guard<std::mutex> mlock(Mutex);
	Queue.push(std::move(item));
	Cond.notify_one();
}

UDataRecorder::UDataRecorder() : ClockRateMS(100), Filename("data.csv") { }

UDataRecorder::UDataRecorder(int clockRateMS) : ClockRateMS(clockRateMS), Filename("data.csv") { }

UDataRecorder::UDataRecorder(std::string filename) : ClockRateMS(100), Filename(filename) { }

UDataRecorder::UDataRecorder(int clockRateMS, std::string filename) 
	: ClockRateMS(clockRateMS), Filename(filename) { }

UDataRecorder::UDataRecorder(int clockRateMS, std::string filename, 
	std::vector<std::pair<const void*, DataType>> collectors) 
	: ClockRateMS(clockRateMS), Filename(filename), Collectors(collectors) { }

void UDataRecorder::ReadFromCollectors()
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
				/*
				Collectors[i].first is a void* to get the value we must cast it to a real type
				(T *) casts void* to pointer of type T
				*(T *) dereferences void* for get actual value
				We then add data with value.Clone() to ensure we don't overwrite the value on next loop
				*/
			case DataType::BOOL:
			{
				DataValue<bool> value(*(bool *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT:
			{
				DataValue<int> value(*(int *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT8:
			{
				DataValue<int8> value(*(int8 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT16:
			{
				DataValue<int16> value(*(int16 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT32:
			{
				DataValue<int32> value(*(int32 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::INT64:
			{
				DataValue<int64> value(*(int64 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT:
			{
				DataValue<unsigned int> value(*(unsigned int*)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT8:
			{
				DataValue<uint8> value(*(uint8 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT16:
			{
				DataValue<uint16> value(*(uint16 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT32:
			{
				DataValue<uint32> value(*(uint32 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::UINT64:
			{
				DataValue<uint64> value(*(uint64 *)Collectors[i].first);
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::FLOAT:
			{
				DataValue<float> value(*(float *)Collectors[i].first);
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
			case DataType::FSTRING:
			{
				FString fstr = *(FString *)Collectors[i].first;
				DataValue<std::string> value(std::string(TCHAR_TO_UTF8(*fstr)));
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::FNAME:
			{
				FName fstr = *(FName *)Collectors[i].first;
				DataValue<std::string> value(std::string(TCHAR_TO_UTF8(*fstr.ToString())));
				dataPoint.AddData(value.Clone());
				break;
			}
			case DataType::FTEXT:
			{
				FText fstr = *(FText *)Collectors[i].first;
				DataValue<std::string> value(std::string(TCHAR_TO_UTF8(*fstr.ToString())));
				dataPoint.AddData(value.Clone());
				break;
			}
			}
		}
		Push(&dataPoint);

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

std::thread UDataRecorder::StartWriter()
{
	return std::thread([=] { WriteToFile(); });;
}

std::thread UDataRecorder::StartReader()
{
	return std::thread([=] { ReadFromCollectors(); });
}

void UDataRecorder::WriteToFile()
{
	std::fstream fs;
	fs.open(Filename, std::fstream::out | std::fstream::ate);
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

void UDataRecorder::SetClockRate(int clockRateMS)
{
	ClockRateMS = clockRateMS;
}

int UDataRecorder::GetClockRate()
{
	return ClockRateMS;
}

void UDataRecorder::AddCollector(const void* ptr, DataType type)
{
	Collectors.push_back(std::pair<const void*, DataType>(ptr, type));
}

void UDataRecorder::AddCollectors(std::vector<std::pair<const void*, DataType>> collectors)
{
	Collectors.insert(Collectors.end(), collectors.begin(), collectors.end());
}

void UDataRecorder::Start()
{
	ReaderThread = StartReader();
	WriterThread = StartWriter();
}

void UDataRecorder::Stop()
{
	bStop = true;
	Cond.notify_all();

	ReaderThread.join();
	WriterThread.join();
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
