#include "MessageReceiver.h"

void IMessageReceiver::Initialization(float aMinSNR)
{
	MinSNR = aMinSNR;
}

float IMessageReceiver::GetFrequency() const
{
	return Frequency;
}

void IMessageReceiver::SetFrequency(const float NewFrequency)
{
	Frequency = NewFrequency;
}
