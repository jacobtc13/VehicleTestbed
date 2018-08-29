#include "EventRecorder.h"
#include "Paths.h"

typedef UEventRecorder::FRecordableEvent FRecordableEvent;

std::condition_variable UEventRecorder::condWaiter;
std::atomic<bool> UEventRecorder::bStop = false;
std::atomic<bool> UEventRecorder::bPause = false;
std::queue<UEventRecorder::EventRef> UEventRecorder::writeQueue;
std::mutex UEventRecorder::queueMutex;
FString UEventRecorder::fileName = FPaths::ProjectDir() + FString("Logs/events.xml");
std::thread UEventRecorder::writerThread;
UEventRecorder::Destructor UEventRecorder::destructor;

void UEventRecorder::RecordEvent(EventRef rEvent)
{
	// Don't record new events if it's stopped
	if (!bStop && !bPause)
	{
		Push(rEvent);
	}
}

void UEventRecorder::RecordEvent(const FString aName, const UObject* aHandler)
{
	if (aHandler != nullptr)
		RecordEvent(EventRef(new FRecordableEvent(aName, aHandler)));
}

void UEventRecorder::RecordEventWithDetails(const FString aName, const UObject* aHandler, const TMap<FString, FString> details)
{
	if (aHandler != nullptr)
		RecordEvent(EventRef(new FRecordableEvent(aName, aHandler, details)));
}

void UEventRecorder::Start()
{
	// Do nothing if the recorder has already started
	if (!writerThread.joinable())
	{
		bStop = false;
		bPause = false;
		writerThread = std::thread(WriteThreadFunction);
	}
}

void UEventRecorder::Pause()
{
	// Don't let it pause if it's trying to stop
	if (!bStop)
	{
		bPause = true;
	}
}

void UEventRecorder::Resume()
{
	bPause = false;
	condWaiter.notify_all();
}

void UEventRecorder::Stop()
{
	// Do nothing if the recorder has already stopped
	if (!bStop)
	{
		bStop = true;
		bPause = false;
		condWaiter.notify_all();
		if (writerThread.joinable())
			writerThread.join();
	}
}

// Private functions

void UEventRecorder::Push(const EventRef rEventRef)
{
	queueMutex.lock();
	writeQueue.push(rEventRef);
	queueMutex.unlock();
}

const bool UEventRecorder::Pop(EventPtr& rEventPtr)
{
	queueMutex.lock();
	if (!writeQueue.empty())
	{
		rEventPtr = writeQueue.front();
		writeQueue.pop();
		queueMutex.unlock();
		return true;
	}
	queueMutex.unlock();
	return false;
}

void UEventRecorder::CheckForPause()
{
	std::unique_lock<std::mutex> lock;
	while (bPause)
	{
		condWaiter.wait(lock);
	}
}

void WriteToFile(TArray<FString>& eventsInXMLArray, const FString& file)
{
	// This method handles creating, opening, and closing the file
	if (FFileHelper::SaveStringArrayToFile(eventsInXMLArray, *file, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append))
	{
		eventsInXMLArray.Empty(); // clears the array
	}
}

void UEventRecorder::Write()
{
	// SaveStringArrayToFile() handles the addition of line endings
	TArray<FString> rEventsInXML;
	EventPtr rEventPtr;
	while (Pop(rEventPtr))
	{
		rEventsInXML.Append(rEventPtr->GetXMLFormattedOutput());

		// Simple optimization - Write in batches of 1000 lines
		if (rEventsInXML.Num() > 1000) // This checks number of lines in the array, not number of events
		{
			WriteToFile(rEventsInXML, fileName);
		}
	}
	// If Queue is empty we may as well write whatever events we've currently got
	if (rEventsInXML.Num()) // false = 0, true = everything else
	{
		WriteToFile(rEventsInXML, fileName);
	}
}

void UEventRecorder::WriteThreadFunction()
{
	while (!bStop)
	{
		Write();
		CheckForPause();
	}
	// One last check to catch any events that may have been pushed between the last check and bStop being set
	Write();
}

const TArray<FString> FRecordableEvent::GetXMLFormattedOutput() const
{
	TArray<FString> output;
	output.Add("<event>");
	output.Add("\t<time>" + timestamp + "</time>");
	output.Add("\t<gametime>" + gameTimestamp + "</gametime>");
	output.Add("\t<name>" + name + "</name>");
	output.Add("\t<handler>" + handler + "</hander>");
	for (const FRecordableEvent::Pair& pair : details)
	{
		output.Add("\t<" + pair.Key + ">" + pair.Value + "</" + pair.Key + ">");
	}
	output.Add("</event>");

	return output;
}
