#include "MessageSender.h"
#include "CommDistributor.h"

void IMessageSender::Initialization(float aFrequency, float aMaxSignalStrength, float aVariance)
{
	Frequency = aFrequency;
	MaxSignalStrength = aMaxSignalStrength;
	Variance = aVariance;
}

void IMessageSender::Send(const IMessage& Message, float SignalStrength)
{
	if (UObject* ThisObject = Cast<UObject>(this))
	{
		UCommDistributor::Send(Message, ThisObject, MaxSignalStrength * SignalStrength);
	}
}

float IMessageSender::GetFrequency() const
{
	return Frequency;
}

void IMessageSender::SetFrequency(const float& NewFrequency)
{
	if (NewFrequency > 0)
		Frequency = NewFrequency;
}

float IMessageSender::GetVariance() const
{
	return Variance;
}

void IMessageSender::SetVariance(const float NewVariance)
{
	Variance = NewVariance;
}
