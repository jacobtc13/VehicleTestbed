#include "PerfectTransceiver.h"
#include "GameFramework/Actor.h"
#include "Communication/MessageTemplate.h"

UPerfectTransceiver::UPerfectTransceiver()
{
	PrimaryComponentTick.bCanEverTick = false;

	ISendsMessage::Initialization(0, 0);
	IReceivesMessage::Initialization(0);
}

UPerfectTransceiver::UPerfectTransceiver(float aFrequency, float aMaxSignalStrength, float aMinSNR)
{
	Init(aFrequency, aMaxSignalStrength, aMinSNR);
}


void UPerfectTransceiver::Init(float aFrequency, float aMaxSignalStrength, float aMinSNR)
{
	ISendsMessage::Initialization(aFrequency, aMaxSignalStrength);
	IReceivesMessage::Initialization(aMinSNR);
}

void SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// No inputs to setup
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
		//Send(TMessageTemplate<EResponseCode>(Garbled));
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
				// Logic of attempting to resend the message would go here
				// In this example transceiver the message is not resent
				break;
			case Received:
				// Logic of what to do when the receiver confirms they have received the message
				break;
			default:
				break;
			}
		}
	}
}

FVector UPerfectTransceiver::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}
