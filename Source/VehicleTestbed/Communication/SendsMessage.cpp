#include "SendsMessage.h"

void ISendsMessage::Initialization(float aFrequency, float aMaxSignalStrength, PowerFunction function)
{
	frequency = aFrequency;
	maxSignalStrength = aMaxSignalStrength;
	CalculatePower = function;
}

void ISendsMessage::Send(const Message message, float signalStrength)
{
	// TODO: Link up with the CommunicationDistributor class
}
