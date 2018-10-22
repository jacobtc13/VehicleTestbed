#include "PerfectTransceiver.h"
#include "MessageTemplate.h"
#include "TransceiverControllerComponent.h"
#include "GameFramework/Pawn.h"

UPerfectTransceiver::UPerfectTransceiver()
{
	PrimaryComponentTick.bCanEverTick = false;

	IMessageSender::Initialization(0, 0);
	IMessageReceiver::Initialization(0);
}

UPerfectTransceiver::UPerfectTransceiver(float aFrequency, float aMaxSignalStrength, float aMinSNR)
{
	Init(aFrequency, aMaxSignalStrength, aMinSNR);
}


void UPerfectTransceiver::Init(float aFrequency, float aMaxSignalStrength, float aMinSNR)
{
	IMessageSender::Initialization(aFrequency, aMaxSignalStrength);
	IMessageReceiver::Initialization(aMinSNR);
}
void UPerfectTransceiver::Send(const IMessage& Message, float SignalStrength)
{

}

float UPerfectTransceiver::CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const
{
	if (ActualFrequency == TargetFrequency)
	{
		return TransmissionPower;
	}
	return 0;
}

void UPerfectTransceiver::Receive(const IMessage& message, float SNR)
{
	UEventRecorder::RecordEvent(TEXT("Received message"), this);

	if (SNR <= 0)
	{
		// Can't distinguish from background noise
		// Do nothing (ignore it)
	}
	else if (SNR < MinSNR)
	{
		// Heard something but cannot understand message
	}
	else
	{
		// Received Message loud enough to understand
		// Send it to the player controller of the pawn this is attached to
		UTransceiverControllerComponent* TransceiverLogic = ((APawn*)GetOwner())->GetController()->FindComponentByClass<UTransceiverControllerComponent>();
		if (TransceiverLogic != nullptr)
		{
			TransceiverLogic->InterpretMessage(message);
		}
	}
}

FVector UPerfectTransceiver::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}
