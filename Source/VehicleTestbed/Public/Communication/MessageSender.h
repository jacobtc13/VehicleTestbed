#pragma once

#include "TranceiverBase.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MessageSender.generated.h"

UINTERFACE(MinimalAPI)
class UMessageSender : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API IMessageSender : public ITranceiverBase
{
	GENERATED_BODY()

public:
	///<summary>Initializes the sender with a frequency and maximum signal strength</summary>
	///<param name="aFrequency">The frequency to send messages on</param>
	///<param name="aMaxSignalStrength">The maximum signal strength this sender can output in decibels</param>
	virtual void Initialization(float aFrequency, float aMaxSignalStrength);

	///<summary>Sends a message</summary>
	///<param name="Message">The message to be sent</param>
	///<param name="SignalStrength">The percentage of the maximum signal strength to transmit at. Values between 0 to 1</param>
	virtual void Send(const IMessage& Message, float SignalStrength = 1);

	///<summary>Calculates the power messages are sent at in nearby frequencies</summary>
	///<param name="TransmissionPower">The power at which a message was sent</param>
	///<param name="TargetFrequency">The target frequency this sender has sent a message on</param>
	///<param name="ActualFrequency">The nearby frequency to calculate the transmission power of</param>
	///<returns>The tranmission power a message was sent at on a nearby frequency</returns>
	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const = 0;

	///<summary>Returns the frequency used by this sender</summary>
	///<returns>The frequency used by this sender</returns>
	virtual float GetFrequency() const;

	///<summary>Sets the frequency of this sender</summary>
	///<param name="NewFrequency">The new frequency for this sender</param>
	virtual void SetFrequency(const float& NewFrequency);

protected:
	float Frequency;
	float MaxSignalStrength;
};
