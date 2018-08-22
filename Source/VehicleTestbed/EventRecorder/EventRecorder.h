#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "FileHelper.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventRecorder.generated.h"

UCLASS()
///<summary>Collects details of events and writes them to a file</summary>
class VEHICLETESTBED_API UEventRecorder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	struct FRecordableEvent;
private:
	class Destructor;

	// variables
private:
	static Destructor destructor;
	static std::thread WriterThread;

	static std::queue<FRecordableEvent> WriteQueue;

	static std::mutex QueueMutex;

	static FString FileName;

	static std::atomic<bool> bPause;
	static std::atomic<bool> bStop;
	static std::condition_variable C;

	// functions
public:
	// This function is not a UFUNCTION because it is not designed to be called from blueprints
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name ="rEvent">An FRecordableEvent object to be added to the queue</param>
	static void RecordEvent(const FRecordableEvent rEvent);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="aName">Name of the event which was triggered</param>
	///<param name="aHandler">Name of the object which is handling the event</param>
	static void RecordEvent(const FString aName, const FString aHandler);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="aName">Name of the event which was triggered</param>
	///<param name="aHandler">Name of the object which is handling the event</param>
	///<param name="details">A TMap of key-value pairs to log</param>
	static void RecordEventWithDetails(const FString aName, const FString aHandler, const TMap<FString, FString> details);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Creates a thread running <see cref="Write()" /></summary>
	static void Start();

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Sets the pause variable to true, causing the WriterThread to pause when it next checks the boolean's value</summary>
	static void Pause();

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Sets the pause variable to false, causing the waiting WriterThread to unpause</summary>
	static void Resume();

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Sets the stop variable to true, causing the WriterThread to complete gracefully when it next checks the boolean's value</summary>
	static void Stop();

private:
	///<summary>Checks whether the WriteQueue is empty, thread safe</summary>
	///<returns>True if the queue is empty, false if not</returns>
	static const bool QueueEmpty();
	///<summary>Loop function which is run by the WriterThread.  When the queue of events is not empty it will write their details to a file one by one</summary>
	static void Write();
	///<summary>Checks the value of bPause and waits on the condition variable if it is true</summary>
	static void CheckForPause();

public:
	///<summary>A simple structure to hold information about an event trigger</summary>
	struct FRecordableEvent
	{
	public:
		typedef TPair<FString, FString> Pair;

		const FString Timestamp;
		const FString Name;
		const FString Handler;

		const TMap<FString, FString> Details;

		FRecordableEvent(const FString aName, const FString aHandler, const TMap<FString, FString> details)
			: Timestamp(FDateTime::Now().ToString(*FString("%d/%m/%Y - %H:%M:%S.%s"))),
			Name(aName), Handler(aHandler), Details(details)
		{}
	};

private:
	///<summary>Calls <see cref="Stop()" /> on destruction.  Use as a static variable and make sure it's initialized last</summary>
	class Destructor
	{
	public:
		~Destructor()
		{
			Stop();
		}
	};
};
