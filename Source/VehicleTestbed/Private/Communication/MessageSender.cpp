#include "MessageSender.h"
#include "CommDistributor.h"

void IMessageSender::Initialization(float aFrequency, float aMaxSignalStrength)
{
	Frequency = aFrequency;
	MaxSignalStrength = aMaxSignalStrength;
}

void IMessageSender::Send(const IMessage& Message, float SignalStrength)
{
	if (UObject* ThisObject = Cast<UObject>(this))
	{
		UCommDistributor::Send(Message, ThisObject, MaxSignalStrength * SignalStrength);
	}
}

void IMessageSender::ChangeFrequency(const float& NewFrequency)
{
	Frequency = NewFrequency;
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
