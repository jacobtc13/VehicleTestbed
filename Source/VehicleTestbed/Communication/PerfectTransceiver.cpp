#include "PerfectTransceiver.h"
#include "GameFramework/Actor.h"
#include "MessageTemplate.h"

UPerfectTransceiver::UPerfectTransceiver()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	ISendsMessage::Initialization(0, 0);
	IReceivesMessage::Initialization(0);
}

void UPerfectTransceiver::Initialization(float aFrequency, float aMaxSignalStrength, float aMinSNR)
{
	ISendsMessage::Initialization(aFrequency, aMaxSignalStrength);
	IReceivesMessage::Initialization(aMinSNR);
}

void UPerfectTransceiver::BeginPlay()
{
	UActorComponent::BeginPlay();
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
	if (SNR <= 0)
	{
		// Can't distinguish from background noise
		// Do nothing (ignore it)
	}
	else if (SNR < MinSNR)
	{
		// Heard something but cannot understand message
		Send(TMessageTemplate<EResponseCode>(Garbled));
	}
	else
	{
		// Received Message loud enough to understand
		Send(TMessageTemplate<EResponseCode>(Received));

		if (Cast<TMessageTemplate<EResponseCode>>(&message) != nullptr)
		{
			EResponseCode ResponseCode = Cast<TMessageTemplate<EResponseCode>>(&message)->Get();
			switch (ResponseCode)
			{
			case Garbled:
			{

			}
			}
		}
	}
}

FVector UPerfectTransceiver::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}
