#pragma once

#include"CoreMinimal.h"
#include"Blueprint.generated.h"
#include<queue>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

class VEHICLETESTBED_API EventRecorder
{
	// variables
public:
	static std::queue<struct RecordableEvent> WriteQueue;

private:
	static std::mutex QueueMutex;

	static std::ofstream Writer;
	static std::string FileName;

	static std::thread WriterThread;
	static bool bPause;
	static bool bStop;
	static std::condition_variable C;

	// functions
public:
	UFUNCTION(BlueprintCallable, Category="Events")
	static void AddEvent(const std::string aName, const std::string aHandler);

	static void Start();
	static void Stop();

private:
	static void Write();

	static void CheckForPause();
};

typedef struct RecordableEvent
{
	const std::string Name;
	const std::string Timestamp;
	const std::string Handler;

	RecordableEvent(const std::string aName, const std::string aHandler);
};
