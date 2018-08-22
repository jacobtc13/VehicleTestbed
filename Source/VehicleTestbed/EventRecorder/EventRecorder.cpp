#include "EventRecorder.h"
#include "Paths.h"

typedef UEventRecorder::FRecordableEvent FRecordableEvent;

std::condition_variable UEventRecorder::C;
std::atomic<bool> UEventRecorder::bStop = false;
std::atomic<bool> UEventRecorder::bPause = false;
std::queue<FRecordableEvent> UEventRecorder::WriteQueue = std::queue<FRecordableEvent>();
std::mutex UEventRecorder::QueueMutex;
FString UEventRecorder::FileName = FPaths::ProjectDir() + FString("Logs/events.xml");
std::thread UEventRecorder::WriterThread;
UEventRecorder::Destructor UEventRecorder::destructor;

void UEventRecorder::RecordEvent(const FRecordableEvent rEvent)
{
	// Don't record new events if it's stopped
	if (!bStop && !bPause)
	{
		QueueMutex.lock();
		WriteQueue.push(rEvent);
		QueueMutex.unlock();
	}
}

void UEventRecorder::RecordEvent(const FString aName, const FString aHandler)
{
	RecordEvent(FRecordableEvent(aName, aHandler, TMap<FString, FString>()));
}

void UEventRecorder::RecordEventWithDetails(const FString aName, const FString aHandler, const TMap<FString, FString> details)
{
	RecordEvent(FRecordableEvent(aName, aHandler, details));
}

void UEventRecorder::Start()
{
	// Do nothing if the thing has already started
	if (!WriterThread.joinable())
	{
		bStop = false;
		bPause = false;
		WriterThread = std::thread(Write);
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
	C.notify_all();
}

void UEventRecorder::Stop()
{
	// Do nothing if the thing has already stopped
	if (!bStop)
	{
		bStop = true;
		bPause = false;
		C.notify_all();
		if (WriterThread.joinable())
			WriterThread.join();
	}
}

const bool UEventRecorder::QueueEmpty()
{
	bool isEmpty;
	QueueMutex.lock();
	isEmpty = WriteQueue.empty();
	QueueMutex.unlock();
	return isEmpty;
}

void UEventRecorder::CheckForPause()
{
	std::unique_lock<std::mutex> lock;
	while (bPause)
	{
		C.wait(lock);
	}
}

void WriteToFile(TArray<FString>& eventsInXMLArray, const FString& file)
{
	// This method handles creating, opening, and closing the file
	if (FFileHelper::SaveStringArrayToFile(eventsInXMLArray, *(file), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append))
	{
		eventsInXMLArray.Empty(); // clears the array
	}
}

void UEventRecorder::Write()
{
	// SaveStringArrayToFile() handles the addition of line endings
	TArray<FString> rEventsInXML = TArray<FString>();
	while (!bStop || !QueueEmpty())
	{
		while (!QueueEmpty())
		{
			// At this point we know for a fact that WriteQueue.front() will return something valid because the queue is not empty
			QueueMutex.lock();
			FRecordableEvent rEvent = WriteQueue.front();
			WriteQueue.pop();
			QueueMutex.unlock();

			rEventsInXML.Add("<event>");
			rEventsInXML.Add("\t<time>" + rEvent.Timestamp + "</time>");
			rEventsInXML.Add("\t<name>" + rEvent.Name + "</name>");
			rEventsInXML.Add("\t<handler>" + rEvent.Handler + "</hander>");
			for (const FRecordableEvent::Pair& pair : rEvent.Details)
			{
				rEventsInXML.Add("\t<" + pair.Key + ">" + pair.Value + "</" + pair.Key + ">");
			}
			rEventsInXML.Add("</event>");

			// Simple optimization
			if (rEventsInXML.Num() > 1000) // This checks number of lines in the array, not number of events
			{
				WriteToFile(rEventsInXML, FileName);
			}
			CheckForPause();
		}
		// If Queue is empty we may as well write whatever events we've currently got
		if (rEventsInXML.Num()) // false = 0, true = everything else
		{
			WriteToFile(rEventsInXML, FileName);
		}
	}
}
