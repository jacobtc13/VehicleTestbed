#include "RecordableEvent.h"

UEventRecorder::FRecordableEvent::FRecordableEvent(const FString EventName, const UObject* Caller, const TMap<FString, FString> Details)
	: Timestamp(FDateTime::Now().ToString(TEXT("%d/%m/%Y - %H:%M:%S.%s"))),
	GameTimestamp((Caller && Caller->ImplementsGetWorld()) ? FString::SanitizeFloat(Caller->GetWorld()->GetRealTimeSeconds()) : TEXT("n/a")),
	Name(EventName), Caller(Caller ? Caller->GetFName().ToString() : TEXT("n/a")), Details(Details)
{}

UEventRecorder::FRecordableEvent::~FRecordableEvent()
{}

UEventRecorder::FRecordableEvent::FRecordableEvent(const FRecordableEvent& Other)
	: Timestamp(Other.Timestamp), GameTimestamp(Other.GameTimestamp), 
	Name(Other.Name), Caller(Other.Caller), Details(Other.Details) // This is what the compiler would auto-generate
{}

const TArray<FString> UEventRecorder::FRecordableEvent::GetXMLFormattedOutput() const
{
	TArray<FString> Output;
	Output.Add(TEXT("<event>"));
	Output.Add(TEXT("\t<time>") + Timestamp + TEXT("</time>"));
	Output.Add(TEXT("\t<gametime>") + GameTimestamp + TEXT("</gametime>"));
	Output.Add(TEXT("\t<name>") + Name + TEXT("</name>"));
	Output.Add(TEXT("\t<handler>") + Caller + TEXT("</hander>"));
	for (const FRecordableEvent::Pair& Pair : Details)
	{
		Output.Add(TEXT("\t<") + Pair.Key + TEXT(">") + Pair.Value + TEXT("</") + Pair.Key + TEXT(">"));
	}
	Output.Add(TEXT("</event>"));

	return Output;
}
