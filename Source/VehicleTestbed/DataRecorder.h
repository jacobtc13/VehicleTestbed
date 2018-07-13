#pragma once

#include "CoreMinimal.h"
#include "DataPoint.h"
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
//#include "DataRecorder.generated.h"

class VEHICLETESTBED_API DataRecorder
{
private:
	std::mutex Mutex;
	std::queue<DataPoint> Queue;
	std::condition_variable Cond;
	std::atomic<bool> bStop;
	std::thread ReaderThread;
	std::thread WriterThread;

	std::vector<const void*> Collectors;
	UPROPERTY()
	std::atomic<int> ClockRateMS;

	UPROPERTY()
	std::string Filename;
		
	void ReadFromCollectors();
	void WriteToFile();

	// Queue Operators
	DataPoint& Pop();
	void Pop(DataPoint& item);
	void Push(const DataPoint& item);
	void Push(DataPoint&& item);

public:
	DataRecorder();
	DataRecorder(int clockRateMS);
	DataRecorder(int clockRateMS, std::vector<const void*> collectors);

	std::thread StartReader();
	std::thread StartWriter();
	void SetClockRate(int aRate);
	int GetClockRate();
	void AddCollector(const void* collector);
	void AddCollectors(std::vector<const void*> collectors);
	void Start();
	void Stop();
};





