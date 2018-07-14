#pragma once

#include "CoreMinimal.h"
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
	// Threading variables
	std::mutex Mutex;
	std::queue<DataPoint*> Queue;
	std::condition_variable Cond;
	std::atomic<bool> bStop;
	std::thread ReaderThread;
	std::thread WriterThread;

	std::vector<std::pair<const void*, DataType>> Collectors;
	std::atomic<int> ClockRateMS;

	std::string Filename;

	///<summary>Read the value from all collectors, save in datapoint and push onto queue</summary>
	void ReadFromCollectors();

	///<summary>Write <see cref="Datapoint"> from queue to output file</summary> 
	void WriteToFile();

	// Queue Operators
	///<summary>Get top DataPoint* from Queue and point item at it, then pop queue</summary>
	///<param name="item">Datapoint reference to assign to top item</param>
	///<returns>True if successful, false if queue is empty</summary>
	bool Pop(DataPoint& item);

	///<summary>Adds a DataPoint to the queue</summary>
	///<param name="item">DataPoint to add</param>
	void Push(DataPoint* item);

public:
	///<summary>Default constructor, sets clock rate to 100ms and filename to 'data.csv'</summary>
	DataRecorder();

	///<summary>Constructor with clock rate, sets filename to 'data.csv'</summary>
	///<param name="clockRateMS">Clock rate to use</param>
	DataRecorder(int clockRateMS);

	///<summary>Constructor with filename, sets clock rate to 100ms</summary>
	///<param name="filename">Output filename</param>
	DataRecorder(std::string filename);

	///<summary>Constructor with clock rate</summary>
	///<param name="clockRateMS">Clock rate to use</param>
	///<param name="filename">Output filename</param>
	DataRecorder(int clockRateMS, std::string filename);

	///<summary>Constructor with clock rate and collectors list</summary>
	///<param name="clockRateMS">Clock rate to use</param>
	///<param name="filename">Output filename</param>
	///<param name="collectors">Vector of collectors, pointer and datatype pair</param>
	DataRecorder(int clockRateMS, std::string filename, std::vector<std::pair<const void*, DataType>> collectors);

	///<summary>Spawns a thread calling <see cref="ReadFromCollectors()" /></summary>
	///<returns><see cref="std::thread"/> reference for spawned thread</returns>
	std::thread StartReader();

	///<summary>Spawns a thread calling <see cref="WriteToFile()" /></summary>
	///<returns><see cref="std::thread"/> reference for spawned thread</returns>
	std::thread StartWriter();

	///<summary>Sets Clock Rate</summary>
	///<param name="clockRateMS">Clock rate in ms</param>
	void SetClockRate(int clockRateMS);

	///<summary>Gets the current clock rate</summary>
	///<returns>Current clock rate in ms</returns>
	int GetClockRate();

	///<summary>Add a new collector</summary>
	///<param name="collector">Const Pointer to the data to collect</param>
	///<param name="type"><see cref="DataType"> of the pointer</param>
	void AddCollector(const void* collector, DataType type);

	///<summary>Add a vector of collectors</summary>
	///<param name="collectors">Vector of collectors to add</param>
	void AddCollectors(std::vector<std::pair<const void*, DataType>> collectors);

	///<summary>Calls <see cref="StartReader()"/> and <see cref="StartWriter()"/> 
	/// and stores the thread references</summary>
	void Start();

	///<summary>Joins running threads and ends execution</summary>
	void Stop();
};

