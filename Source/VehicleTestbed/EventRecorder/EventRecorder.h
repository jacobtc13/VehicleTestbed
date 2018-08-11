#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "FileHelper.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventRecorder.generated.h"

///<summary>Collects details of events and writes them to a file</summary>
UCLASS()
class VEHICLETESTBED_API UEventRecorder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	// variables
private:
	static std::queue<struct FRecordableEvent> WriteQueue;

	static std::mutex QueueMutex;

	static FString FileName;

	static std::thread WriterThread;
	static std::atomic<bool> bPause;
	static std::atomic<bool> bStop;
	static std::condition_variable C;

	// functions
public:
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="aName">Name of the event which was triggered</param>
	///<param name="aHandler">Name of the object which is handling the event</param>
	UFUNCTION(BlueprintCallable, Category="EventRecorder")
	static void AddEventToQueue(const FString aName, const FString aHandler);

	///<summary>Creates a thread running <see cref="Write()" /></summary>
	UFUNCTION(BlueprintCallable, Category="EventRecorder")
	static void Start();
	///<summary>Sets the pause variable to true, causing the WriterThread to pause when it next checks the boolean's value</summary>
	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	static void Pause();
	///<summary>Sets the pause variable to false, causing the waiting WriterThread to unpause</summary>
	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	static void Resume();
	///<summary>Sets the stop variable to true, causing the WriterThread to complete gracefully when it next checks the boolean's value</summary>
	UFUNCTION(BlueprintCallable, Category="EventRecorder")
	static void Stop();

private:
	///<summary>Loop function which is run by the WriterThread.  When the queue of events is not empty it will write their details to a file one by one</summary>
	static void Write();
	///<summary>Checks the value of bPause and waits on the condition variable if it is true</summary>
	static void CheckForPause();
};

///<summary>A simple structure to hold information about an event trigger</summary>
typedef struct FRecordableEvent
{
	const FString Name;
	const FString Timestamp;
	const FString Handler;

	FRecordableEvent(const FString aName, const FString aHandler);
};
