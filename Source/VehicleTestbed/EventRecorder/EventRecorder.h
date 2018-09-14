#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "FileHelper.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventRecorder.generated.h"

// Abstract tag blocks instantiation of this class.  It is pointless to do so anyway.
UCLASS(Abstract)
///<summary>Collects details of events and writes them to a file</summary>
class VEHICLETESTBED_API UEventRecorder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	class FRecordableEvent;
	typedef TSharedRef<const FRecordableEvent> EventRef;

private:
	class FDestructor;
	typedef TSharedPtr<const FRecordableEvent> EventPtr;

	// variables
private:
	static FDestructor Destructor;
	static std::thread WriterThread;
	static std::queue<EventRef> WriteQueue;
	static std::mutex QueueMutex;

	static FString FileName;

	static std::atomic<bool> bStop;

	// functions
public:
	// This function is not a UFUNCTION because it is not designed to be called from blueprints
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name ="REvent">An FRecordableEvent object to be added to the queue</param>
	static void RecordEvent(EventRef REvent);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="EventName">Name of the event which was triggered</param>
	///<param name="Caller">Pointer to the UObject which called this function</param>
	static void RecordEvent(const FString EventName, const UObject* Caller);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="EventName">Name of the event which was triggered</param>
	///<param name="Caller">Pointer to the UObject which called this funtion</param>
	///<param name="Details">A TMap of key-value pairs to log</param>
	static void RecordEventWithDetails(const FString EventName, const UObject* Caller, const TMap<FString, FString> Details);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Creates a thread running <see cref="Write()" /></summary>
	///<returns>True if the thread was started, false if it was already running.</returns>
	static const bool Start();

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Sets the stop variable to true, causing the WriterThread to complete gracefully when it next checks the boolean's value</summary>
	static void Stop();

private:
	///<summary>Adds a recordable event to the queue</summary>
	///<param name="REventRef">A shared reference (smart pointer) of a recordable event</param>
	static void Push(const EventRef REventRef);

	///<summary>Pops the front of the queue and sets the passed pointer to it</summary>
	///<param name="OutEventPtr">Gets set to what used to be the front of the queue</param>
	///<returns>True if the pop was successful, false otherwise</returns>
	static const bool Pop(EventPtr& OutEventPtr);

	///<summary>Loops until the write queue is empty and writes the events to a file in batches for better performance</summary>
	static void Write();

	///<summary>Loop function which is run by the WriterThread.</summary>
	static void WriteThreadFunction();

private:
	///<summary>Calls <see cref="Stop()" /> on destruction.  Use as a static variable and make sure it's initialized last</summary>
	class FDestructor
	{
	public:
		~FDestructor();
	};
};
