#include "EventRecorder.h"
#include "RecordableEvent.h"
#include "Paths.h"

std::atomic<bool> UEventRecorder::bStop = false;
std::queue<UEventRecorder::EventRef> UEventRecorder::WriteQueue;
std::mutex UEventRecorder::QueueMutex;
FString UEventRecorder::FolderName = FPaths::ProjectDir() + TEXT("Logs");
FString UEventRecorder::FileName;
std::future<void> UEventRecorder::WriterThread;
UEventRecorder::FDestructor UEventRecorder::Destructor;

UEventRecorder::FDestructor::~FDestructor()
{
	Stop();
	if (WriterThread.valid())
		WriterThread.wait();
}

void UEventRecorder::RecordEvent(EventRef REvent)
{
	// Don't record new events if it's stopped
	if (!bStop)
	{
		Push(REvent);
	}
}

void UEventRecorder::RecordEvent(const FString EventName, const UObject* Caller)
{
	if (Caller != nullptr)
		RecordEvent(EventRef(new FRecordableEvent(EventName, Caller)));
}

void UEventRecorder::RecordEventWithDetails(const FString EventName, const UObject* Caller, const TMap<FString, FString> Details)
{
	if (Caller != nullptr)
		RecordEvent(EventRef(new FRecordableEvent(EventName, Caller, Details)));
}

const bool isWriterThreadFinished(const std::future<void>& WriterThread)
{
	using namespace std::chrono_literals;
	if (WriterThread.valid())
		return WriterThread.wait_for(0ms) == std::future_status::ready;
	else
		// not valid means it has either not run or has returned and `get()` has been called
		// in either case it is ready to be started
		return true;
}

const bool UEventRecorder::Start()
{
	// Do nothing if the recorder has already started
	if (isWriterThreadFinished(WriterThread))
	{
		bStop = false;
		// Set the target filename to reflect the newly starting run. The file won't exist until the recorder tries to write
		FileName = FolderName + TEXT("/events-") + FDateTime::Now().ToString(TEXT("%d.%m.%Y-%H.%M.%S")) + TEXT(".xml");

		WriterThread = std::async(std::launch::async, WriteThreadFunction);
		return true;
	}
	return false;
}

void UEventRecorder::Stop()
{
	// Do nothing if the recorder has already stopped
	if (!bStop)
	{
		bStop = true;
	}
}

FString UEventRecorder::GetFolderOutput()
{
	return FolderName;
}

void UEventRecorder::SetFolderOutput(FString NewFolderLocation)
{
	// Remove the ending slash if its there
	NewFolderLocation.RemoveFromEnd(TEXT("/"));
	NewFolderLocation.RemoveFromEnd(TEXT("\\"));
	FolderName = NewFolderLocation;
}

// Private functions

void UEventRecorder::Push(const EventRef REventRef)
{
	QueueMutex.lock();
	WriteQueue.push(REventRef);
	QueueMutex.unlock();
}

const bool UEventRecorder::Pop(EventPtr& OutEventPtr)
{
	QueueMutex.lock();
	if (!WriteQueue.empty())
	{
		OutEventPtr = WriteQueue.front();
		WriteQueue.pop();
		QueueMutex.unlock();
		return true;
	}
	QueueMutex.unlock();
	return false;
}

void WriteToFile(TArray<FString>& EventsInXMLArray, const FString& File)
{
	// This method handles creating, opening, and closing the file
	if (FFileHelper::SaveStringArrayToFile(EventsInXMLArray, *File, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append))
	{
		EventsInXMLArray.Empty(); // clears the array
	}
}

void UEventRecorder::Write()
{
	// SaveStringArrayToFile() handles the addition of line endings
	TArray<FString> REventsInXML;
	EventPtr REventPtr;
	while (Pop(REventPtr))
	{
		REventsInXML.Append(REventPtr->GetXMLFormattedOutput());

		// Simple optimization - Write in batches of 1000 lines
		if (REventsInXML.Num() > 1000) // This checks number of lines in the array, not number of events
		{
			WriteToFile(REventsInXML, FileName);
		}
	}
	// If Queue is empty we may as well write whatever events we've currently got
	if (REventsInXML.Num()) // false = 0, true = everything else
	{
		WriteToFile(REventsInXML, FileName);
	}
}

void UEventRecorder::WriteThreadFunction()
{
	while (!bStop)
	{
		Write();
	}
	// One last check to catch any events that may have been pushed between the last check and bStop being set
	Write();
}
