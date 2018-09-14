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

	static std::atomic<bool> bPause;
	static std::atomic<bool> bStop;
	static std::condition_variable CondWaiter;

	// functions
public:
	// This function is not a UFUNCTION because it is not designed to be called from blueprints
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name ="rEvent">An FRecordableEvent object to be added to the queue</param>
	static void RecordEvent(EventRef rEvent);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="aName">Name of the event which was triggered</param>
	///<param name="aHandler">Name of the object which is handling the event</param>
	static void RecordEvent(const FString aName, const UObject* aHandler);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Collects data about an event and adds it to the queue to be written</summary>
	///<param name="aName">Name of the event which was triggered</param>
	///<param name="aHandler">Name of the object which is handling the event</param>
	///<param name="details">A TMap of key-value pairs to log</param>
	static void RecordEventWithDetails(const FString aName, const UObject* aHandler, const TMap<FString, FString> details);

	UFUNCTION(BlueprintCallable, Category = "EventRecorder")
	///<summary>Creates a thread running <see cref="Write()" /></summary>
	///<returns>True if the thread was started, false if it was already running.</returns>
	static const bool Start();

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
	///<summary>Adds a recordable event to the queue</summary>
	///<param name="rEventRef">A shared reference (smart pointer) of a recordable event</param>
	static void Push(const EventRef rEventRef);

	///<summary>Pops the front of the queue and sets the passed pointer to it</summary>
	///<param name="rEventPtr">Gets set to what used to be the front of the queue</param>
	///<returns>True if the pop was successful, false otherwise</returns>
	static const bool Pop(EventPtr& OutEventPtr);

	///<summary>Loops until the write queue is empty and writes the events to a file in batches for better performance</summary>
	static void Write();

	///<summary>Loop function which is run by the WriterThread.</summary>
	static void WriteThreadFunction();

	///<summary>Checks the value of bPause and waits on the condition variable if it is true</summary>
	static void CheckForPause();

private:
	///<summary>Calls <see cref="Stop()" /> on destruction.  Use as a static variable and make sure it's initialized last</summary>
	class FDestructor
	{
	public:
		~FDestructor()
		{
			Stop();
			if (WriterThread.joinable())
				WriterThread.join();
		}
	};


public:
	///<summary>A simple class to hold information about an event trigger</summary>
	class FRecordableEvent
	{
	public:
		typedef TPair<FString, FString> Pair;

		const FString timestamp;
		const FString gameTimestamp;
		const FString name;
		const FString handler;

		const TMap<FString, FString> details;

		///<summary>Constructor which requires a name and handler</summary>
		///<param name="aName">Name of the event which was triggered</param>
		///<param name="aHandler">Name of the object which is handling the event</param>
		///<param name="details">A TMap of key-value pairs to log</param>
		FRecordableEvent(const FString aName, const UObject* aHandler, const TMap<FString, FString> details = TMap<FString, FString>())
			: timestamp(FDateTime::Now().ToString(*FString("%d/%m/%Y - %H:%M:%S.%s"))),
			gameTimestamp(FString::SanitizeFloat(aHandler->GetWorld()->GetRealTimeSeconds())),
			name(aName), handler(aHandler->GetFName().ToString()), details(details)
		{}

		virtual ~FRecordableEvent()
		{}

		///<summary>Copy Constructor</summary>
		///<param name="other">Another FRecordableEvent object</param>
		FRecordableEvent(const FRecordableEvent& other)
			: timestamp(other.timestamp), name(other.name), handler(other.handler), details(other.details) // This is what the compiler would auto-generate
		{}

		// All member variables are const so can't use the assignment operator (deleted implicitly anyway)
		FRecordableEvent& operator=(const FRecordableEvent& other) = delete;

		///<summary>Gets the info in an XML format as an array of lines</summary>
		///<returns>An array of FStrings where each element of the array is a new line</returns>
		virtual const TArray<FString> GetXMLFormattedOutput() const;
	};
};
