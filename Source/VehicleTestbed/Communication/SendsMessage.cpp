#include "SendsMessage.h"

void ISendsMessage::Initialization(float aFrequency, float aMaxSignalStrength)
{
	frequency = aFrequency;
	maxSignalStrength = aMaxSignalStrength;
}

const float ISendsMessage::GetFrequency() const
{
	return frequency;
}

void ISendsMessage::SetFrequency(const float& NewFrequency)
{
	if (NewFrequency > 0)
		frequency = NewFrequency;
}
