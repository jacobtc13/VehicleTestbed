#include"EventRecorder.h"

std::queue<RecordableEvent> EventRecorder::WriteQueue = std::queue<RecordableEvent>();
std::ofstream EventRecorder::Writer = std::ofstream();
std::string EventRecorder::FileName = "events.xml";

void EventRecorder::AddEvent(const std::string aName, const std::string aHandler)
{
	RecordableEvent REvent = RecordableEvent(aName, aHandler);
	QueueMutex.lock();
	WriteQueue.push(REvent);
	QueueMutex.unlock();
}

void EventRecorder::Start()
{
	WriterThread = std::thread(Write);
}

void EventRecorder::Stop()
{
	bStop = true;
	C.notify_all();

	WriterThread.join();
}

void EventRecorder::Write()
{
	while (!bStop)
	{
		// locks seem a little disorganized but fear not it works properly
		QueueMutex.lock();
		while (!WriteQueue.empty())
		{
			QueueMutex.unlock();  // unlocking here may seem pointless but it's fine if this thread gets locked out halfway through
								  // and gives more opportunities for waiting events to continue on.
			RecordableEvent* REvent = nullptr;
			QueueMutex.lock();
			REvent = &WriteQueue.front();
			WriteQueue.pop();
			QueueMutex.unlock();

			if (!Writer.is_open())
			{
				Writer.open(FileName);
			}
			
			Writer << "<event>" << std::endl;
			Writer << "\t<name>" << REvent->Name << "</name>" << std::endl;
			Writer << "\t<time>" << REvent->Timestamp << "</time>" << std::endl;
			Writer << "\t<handler>" << REvent->Handler << "</handler>" << std::endl;
			Writer << "</event>" << std::endl;

			CheckForPause();  // Writing is a relatively long operation so now is a good time to check for a pause

			QueueMutex.lock();
		}
		QueueMutex.unlock();

		if (Writer.is_open())
		{
			Writer.close();
		}

		CheckForPause();
	}
}

void EventRecorder::CheckForPause()
{
	std::unique_lock<std::mutex> lock;
	while (EventRecorder::bPause)
	{
		bool WasOpen = false;
		if (Writer.is_open())
		{
			WasOpen = true;
			Writer.close();
		}
		C.wait(lock);
		if (WasOpen)
		{
			Writer.open(FileName);
		}
	}
}

RecordableEvent::RecordableEvent(const std::string aName, const std::string aHandler)
	: Name(aName), Handler(aHandler),
	Timestamp(std::string(TCHAR_TO_UTF8(*(FDateTime::Now().ToString()))))
{}
