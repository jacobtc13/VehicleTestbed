#include "SendsMessage.h"

void ISendsMessage::Initialization(float aFrequency, float aMaxSignalStrength)
{
	frequency = aFrequency;
	maxSignalStrength = aMaxSignalStrength;
}
