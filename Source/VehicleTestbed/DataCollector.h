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

template <typename T>
class DataRecorder
{
private:
	std::mutex mutex_;
	std::queue<DataPoint<T>> queue_;

	DataPoint<T> NIL;

	std::condition_variable cond_;
	std::atomic<int> clockRateMS_;
	std::atomic<bool> exit_;
	std::vector<const T*> collectors_;
	std::string filename_;
	void readFromCollectors();
	void writeToFile();

	DataPoint<T> pop();
	void pop(DataPoint<T>& item);
	void push(const DataPoint<T>& item);
	void push(DataPoint<T>&& item);

public:
	DataRecorder();
	DataRecorder(int clockRateMS);
	DataRecorder(int clockRateMS, std::vector<const T*> collectors);

	std::thread startReader();
	std::thread startWriter();
	void setClockRate(int aRate);
	int getClockRate();
	void addCollector(const T* collector);
	void addCollectors(std::vector<const T*> collectors);
	void exit();
};


template<typename T>
DataPoint<T> DataRecorder<T>::pop()
{
	std::unique_lock<std::mutex> mlock(mutex_);
	while (queue_.empty())
	{
		cond_.wait(mlock);
	}
	auto item = queue_.front();
	queue_.pop();
	return item;
}

template<typename T>
void DataRecorder<T>::pop(DataPoint<T>& item)
{
	std::unique_lock<std::mutex> mlock(mutex_);
	while (queue_.empty())
	{
		cond_.wait(mlock);
	}
	item = queue_.front();
	queue_.pop();
}

template<typename T>
void DataRecorder<T>::push(const DataPoint<T>& item)
{
	std::unique_lock<std::mutex> mlock(mutex_);
	queue_.push(item);
	mlock.unlock();
	cond_.notify_one();
}

template<typename T>
void DataRecorder<T>::push(DataPoint<T>&& item)
{
	std::unique_lock<std::mutex> mlock(mutex_);
	queue_.push(std::move(item));
	mlock.unlock();
	cond_.notify_one();
}

template <typename T>
DataRecorder<T>::DataRecorder()
{
	exit_ = false;
	clockRateMS_ = 100;
}

template<typename T>
DataRecorder<T>::DataRecorder(int clockRateMS)
{
	exit_ = false;
	clockRateMS_ = clockRateMS;
}

template<typename T>
DataRecorder<T>::DataRecorder(int clockRateMS, std::vector<const T*> collectors)
{
	exit_ = false;
	clockRateMS_ = clockRateMS;
	collectors_ = collectors;
}

template <typename T>
std::thread DataRecorder<T>::startReader()
{
	return std::thread([=] { readFromCollectors(); });
}

template <typename T>
void DataRecorder<T>::readFromCollectors()
{
	do {
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::milliseconds milliseconds;
		Clock::time_point t0 = Clock::now();

		DataPoint<float> dataPoint;
		for (std::vector<const T*>::const_iterator iter = collectors_.begin(), end = collectors_.end(); iter != end; ++iter)
		{
			dataPoint.AddData(**iter);
		}
		push(dataPoint);

		Clock::time_point t1 = Clock::now();
		milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10 - ms.count()));
	} while (!exit_);
}

template <typename T>
std::thread DataRecorder<T>::startWriter()
{
	return std::thread([=] { writeToFile(); });;
}

template <typename T>
void DataRecorder<T>::writeToFile()
{
	std::fstream fs;
	fs.open("test.txt", std::fstream::out | std::fstream::ate);
	do {
		auto dataPoint = pop();
		if (dataPoint != NIL)
		{
			fs << dataPoint << std::endl;
		}
	} while (!exit_);

	fs.close();
}

template <typename T>
void DataRecorder<T>::setClockRate(int clockRateMS)
{
	clockRateMS_ = clockRateMS;
}

template <typename T>
int DataRecorder<T>::getClockRate()
{
	return clockRateMS_;
}

template<typename T>
void DataRecorder<T>::addCollector(const T * collector)
{
	collectors_.push_back(collector);
}

template<typename T>
void DataRecorder<T>::addCollectors(std::vector<const T*> collectors)
{
	collectors_.insert(collectors_.end(), collectors.begin(), collectors.end());
}

template <typename T>
void DataRecorder<T>::exit()
{
	exit_ = true;
	push(NIL);
	cond_.notify_all();
}




