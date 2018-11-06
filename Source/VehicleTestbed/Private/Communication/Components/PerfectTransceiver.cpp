#include "PerfectTransceiver.h"
#include "MessageTemplate.h"
#include "TransceiverControllerComponent.h"
#include "GameFramework/Pawn.h"

UPerfectTransceiver::UPerfectTransceiver()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPerfectTransceiver::Initialize(const float aMaxSignalStrength, const float aMinSNR, const float aFrequency, const float aVariance)
{
	SetMaxSignalStrength(aMaxSignalStrength);
	SetMinSNR(aMinSNR);
	SetFrequency(aFrequency);
	SetVariance(aVariance);
}

void UPerfectTransceiver::Send(const UMessage* Message, float SignalStrength)
{
	UEventRecorder::RecordEvent(TEXT("Sending message"), this);
	UCommDistributor::Send(Message, this, MaxSignalStrength * SignalStrength);
}

float UPerfectTransceiver::CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const
{
	if (ActualFrequency == TargetFrequency)
	{
		return TransmissionPower;
	}
	return 0;
}

void UPerfectTransceiver::Receive(const UMessage* Message, float SNR)
{
	TMap<FString, FString> Details;
	Details.Add(TEXT("SNR"), FString::SanitizeFloat(SNR));
	UEventRecorder::RecordEventWithDetails(TEXT("Received message"), this, Details);

	if (SNR >= MinSNR)
	{
		// Received Message loud enough to understand
		// Send it to the player controller of the pawn this is attached to
		if (APawn* Owner = Cast<APawn>(GetOwner()))
		{
			if (UTransceiverControllerComponent* TransceiverLogic = Owner->GetController()->FindComponentByClass<UTransceiverControllerComponent>())
			{
				TransceiverLogic->InterpretMessage(Message);
			}
		}
	}
	else if (SNR > 0)
	{
		// Heard something but cannot understand message
	}
	else
	{
		// Can't distinguish from background noise
		// Do nothing (ignore it)
	}
}

FVector UPerfectTransceiver::GetLocation() const
{
	return GetOwner()->GetActorLocation();
}

float UPerfectTransceiver::GetMaxSignalStrength() const
{
	return MaxSignalStrength;
}

void UPerfectTransceiver::SetMaxSignalStrength(const float NewMaxSignalStrength)
{
	MaxSignalStrength = NewMaxSignalStrength;
}

float UPerfectTransceiver::GetMinSNR() const
{
	return MinSNR;
}

void UPerfectTransceiver::SetMinSNR(const float NewMinSNR)
{
	MinSNR = NewMinSNR;
}

float UPerfectTransceiver::GetFrequency() const
{
	return Frequency;
}

void UPerfectTransceiver::SetFrequency(const float NewFrequency)
{
	UCommDistributor::SwitchChannel(NewFrequency, this);
	Frequency = NewFrequency;
}

float UPerfectTransceiver::GetVariance() const
{
	return Variance;
}

void UPerfectTransceiver::SetVariance(const float NewVariance)
{
	Variance = NewVariance;
}
