#include "SendsMessage.h"

void ISendsMessage::Initialization(float aFrequency, float aMaxSignalStrength)
{
	Frequency = aFrequency;
	MaxSignalStrength = aMaxSignalStrength;
}

void ISendsMessage::ChangeFrequency(const float& NewFrequency)
{
	Frequency = NewFrequency;
}

const float ISendsMessage::GetFrequency() const
{
	return Frequency;
}

void ISendsMessage::SetFrequency(const float& NewFrequency)
{
	if (NewFrequency > 0)
		Frequency = NewFrequency;
}
