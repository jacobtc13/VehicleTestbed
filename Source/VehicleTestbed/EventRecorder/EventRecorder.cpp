#include "EventRecorder.h"
#include "Paths.h"

std::queue<FRecordableEvent> UEventRecorder::WriteQueue = std::queue<FRecordableEvent>();
std::mutex UEventRecorder::QueueMutex;
FString UEventRecorder::FileName = FPaths::ProjectDir() + FString("events.xml");
std::thread UEventRecorder::WriterThread;
std::atomic<bool> UEventRecorder::bPause = false;
std::atomic<bool> UEventRecorder::bStop = false;
std::condition_variable UEventRecorder::C;

void UEventRecorder::RecordEvent(const FString aName, const FString aHandler)
{
	RecordEventWithDetails(aName, aHandler, TMap<FString, FString>());
}

void UEventRecorder::RecordEventWithDetails(const FString aName, const FString aHandler, const TMap<FString, FString> details)
{
	FRecordableEvent REvent = FRecordableEvent(aName, aHandler, details);
	QueueMutex.lock();
	WriteQueue.push(REvent);
	QueueMutex.unlock();
}

void UEventRecorder::Start()
{
	if (!WriterThread.joinable())
	{
		WriterThread = std::thread(Write);
	}
}

void UEventRecorder::Pause()
{
	bPause = true;
}

void UEventRecorder::Resume()
{
	bPause = false;
	C.notify_all();
}

void UEventRecorder::Stop()
{
	bStop = true;
	C.notify_all();

	WriterThread.join();
}

void UEventRecorder::Write()
{
	while (!bStop)
	{
		// locks seem a little disorganized but fear not it works properly
		QueueMutex.lock();
		while (!WriteQueue.empty())
		{
			QueueMutex.unlock();  // unlocking here may seem pointless but it's fine if this thread gets locked out halfway through
								  // and gives more opportunities for waiting events to continue on.
			QueueMutex.lock();
			FRecordableEvent REvent = WriteQueue.front();
			WriteQueue.pop();
			QueueMutex.unlock();

			CheckForPause();  // check for a pause before and after writing

			FString Line = FString("<event>\r\n\t<time>") + REvent.Timestamp + FString("</name>\r\n\t<name>")
				+ REvent.Name + FString("</time>\r\n\t<handler>") + REvent.Handler + FString("</handler>\r\n");

			for (FRecordableEvent::Pair pair : REvent.Details)
			{
				Line.Append(FString("\t<") + pair.Key + FString(">") + pair.Value + FString("</") + pair.Key + FString(">\r\n"));
			}
			Line.Append(FString("</event>\r\n"));

			// This crazy method automatically handles opening, closing and creating the file
			FFileHelper::SaveStringToFile(Line, *FileName, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

			CheckForPause();

			QueueMutex.lock();
		}
		QueueMutex.unlock();

		CheckForPause();
	}
}

void UEventRecorder::CheckForPause()
{
	std::unique_lock<std::mutex> lock;
	while (UEventRecorder::bPause)
	{
		C.wait(lock);
	}
}
