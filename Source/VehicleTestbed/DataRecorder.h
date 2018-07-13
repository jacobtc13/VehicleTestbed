#pragma once

#include <chrono>
#include <fstream>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <utility>

#include "DataPoint.h"
#include "DataType.h"

class VEHICLETESTBED_API DataRecorder
{
private:
	std::mutex Mutex;
	std::queue<DataPoint*> Queue;
	std::condition_variable Cond;
	std::atomic<bool> bStop;
	std::thread ReaderThread;
	std::thread WriterThread;

	std::vector<std::pair<const void*, DataType>> Collectors;
	//UPROPERTY()
	std::atomic<int> ClockRateMS;

	//UPROPERTY()
	std::string Filename;

	void ReadFromCollectors();
	void WriteToFile();

	// Queue Operators
	bool Pop(DataPoint& item);
	void Push(DataPoint* item);

public:
	DataRecorder();
	DataRecorder(int clockRateMS);
	DataRecorder(int clockRateMS, std::vector<std::pair<const void*, DataType>> collectors);

	std::thread StartReader();
	std::thread StartWriter();
	void SetClockRate(int aRate);
	int GetClockRate();
	void AddCollector(const void* collector, DataType type);
	void AddCollectors(std::vector<std::pair<const void*, DataType>> collectors);
	void Start();
	void Stop();
};

