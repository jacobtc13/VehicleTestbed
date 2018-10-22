#include "MessageSender.h"

void IMessageSender::Initialization(float aFrequency, float aMaxSignalStrength)
{
	Frequency = aFrequency;
	MaxSignalStrength = aMaxSignalStrength;
}

void IMessageSender::ChangeFrequency(const float& NewFrequency)
{
	Frequency = NewFrequency;
}

const float IMessageSender::GetFrequency() const
{
	return Frequency;
}

void IMessageSender::SetFrequency(const float& NewFrequency)
{
	if (NewFrequency > 0)
		Frequency = NewFrequency;
}
