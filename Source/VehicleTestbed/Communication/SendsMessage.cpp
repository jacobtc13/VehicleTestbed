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
