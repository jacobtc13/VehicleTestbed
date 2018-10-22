#pragma once

#include "EventRecorder.h"
#include "Engine/World.h"

///<summary>A simple class to hold information about an event trigger</summary>
class UEventRecorder::FRecordableEvent
{
public:
	typedef TPair<FString, FString> Pair;

	const FString Timestamp;
	const FString GameTimestamp;
	const FString Name;
	const FString Caller;

	const TMap<FString, FString> Details;

	///<summary>Constructor which requires a name and handler</summary>
	///<param name="EventName">Name of the event which was triggered</param>
	///<param name="Caller">Pointer to the object which created this event</param>
	///<param name="Details">A TMap of key-value pairs to log</param>
	FRecordableEvent(const FString EventName, const UObject* Caller, const TMap<FString, FString> Details = TMap<FString, FString>());

	///<summary>Virtual destructor</summary>
	virtual ~FRecordableEvent();

	///<summary>Copy Constructor</summary>
	///<param name="Other">Another FRecordableEvent object</param>
	FRecordableEvent(const FRecordableEvent& Other);

	// All member variables are const so can't use the assignment operator (deleted implicitly anyway)
	FRecordableEvent& operator=(const FRecordableEvent& Other) = delete;

	///<summary>Gets the info in an XML format as an array of lines</summary>
	///<returns>An array of FStrings where each element of the array is a new line</returns>
	virtual const TArray<FString> GetXMLFormattedOutput() const;
};
