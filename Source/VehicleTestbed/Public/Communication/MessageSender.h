#pragma once

#include "TranceiverBase.h"
#include "CommDistributor.h"

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
	UFUNCTION()
	///<summary>Sends a message</summary>
	///<param name="Message">The message to be sent</param>
	///<param name="SignalStrength">The percentage of the maximum signal strength to transmit at. Values between 0 to 1</param>
	virtual void Send(const UMessage* Message, float SignalStrength = 1) = 0;

	UFUNCTION()
	///<summary>Calculates the power messages are sent at in nearby frequencies</summary>
	///<param name="TransmissionPower">The power at which a message was sent</param>
	///<param name="TargetFrequency">The target frequency this sender has sent a message on</param>
	///<param name="ActualFrequency">The nearby frequency to calculate the transmission power of</param>
	///<returns>The tranmission power a message was sent at on a nearby frequency</returns>
	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const = 0;

	UFUNCTION()
	///<summary>Gets the maximum signal strength of this sender</summary>
	///<returns>The maximum signal strength in decibels</returns>
	virtual float GetMaxSignalStrength() const = 0;

	UFUNCTION()
	///<summary>Sets the maximum signal strength of this sender</summary>
	///<param name="NewMaxSignalStrength">The new maximum signal strength in decibels</param>
	virtual void SetMaxSignalStrength(const float NewMaxSignalStrength) = 0;

	UFUNCTION()
	///<summary>Returns the frequency used by this sender</summary>
	///<returns>The frequency used by this sender</returns>
	virtual float GetFrequency() const = 0;

	UFUNCTION()
	///<summary>Sets the frequency of this sender</summary>
	///<param name="NewFrequency">The new frequency for this sender</param>
	virtual void SetFrequency(const float NewFrequency) = 0;

	UFUNCTION()
	///<summary>Gets the variance of this sender</summary>
	///<returns>The variance of this sender</returns>
	virtual float GetVariance() const = 0;

	UFUNCTION()
	///<summary>Sets the variance of this sender</summary>
	///<param name="NewVariance">The new variance for this sender</param>
	virtual void SetVariance(const float NewVariance) = 0;
};
