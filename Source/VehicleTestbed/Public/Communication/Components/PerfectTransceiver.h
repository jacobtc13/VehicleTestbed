#pragma once

#include "MessageSender.h"
#include "MessageReceiver.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerfectTransceiver.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETESTBED_API UPerfectTransceiver : public UActorComponent, public IMessageSender, public IMessageReceiver
{
	GENERATED_BODY()

public:
	UPerfectTransceiver();

	UFUNCTION()
	///<summary>Initialises this transceiver</summary>
	///<param name="aMaxSignalStrength">The maximum signal strength this transceiver can output</param>
	///<param name="aMinSNR">The minimum SNR at which this transceiver can correctly interpret messages</param>
	///<param name="aFrequency">The frequency this transceiver sends and receives messages on</param>
	///<param name="aVariance">The variance of the frequency output of this transceiver</param>
	void Initialise(const float aMaxSignalStrength, const float aMinSNR, const float aFrequency, const float aVariance);

	UFUNCTION()
	///<summary>Sends a message out into the world</summary>
	///<param name="Message">The message to be sent</param>
	///<param name="SignalStrength">The percentage of the maximum signal strength to transmit at. Values between 0 to 1</param>
	virtual void Send(const UMessage* Message, float SignalStrength = 1) override;

	UFUNCTION()
	///<summary>Calculates the power messages are sent at in nearby frequencies</summary>
	///<param name="TransmissionPower">The power at which a message was sent</param>
	///<param name="TargetFrequency">The target frequency this sender has sent a message on</param>
	///<param name="ActualFrequency">The nearby frequency to calculate the transmission power of</param>
	///<returns>The tranmission power a message was sent at on a nearby frequency</returns>
	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const override;

	UFUNCTION()
	///<summary>Receives a message with a signal to noise ratio</summary>
	///<param name="Message">The message being received</param>
	///<param name="SNR">The signal to noise ratio</param>
	virtual void Receive(const UMessage* message, float SNR) override;

	UFUNCTION()
	///<summary>Returns the location of this object</summary>
	///<returns>The location of this object</returns>
	virtual FVector GetLocation() const override;

	UFUNCTION()
	///<summary>Gets the maximum signal strength of this transceiver</summary>
	///<returns>The maximum signal strength in decibels</returns>
	virtual float GetMaxSignalStrength() const override;

	UFUNCTION()
	///<summary>Sets the maximum signal strength of this transceiver</summary>
	///<param name="NewMaxSignalStrength">The new maximum signal strength in decibels</param>
	virtual void SetMaxSignalStrength(const float NewMaxSignalStrength) override;

	UFUNCTION()
	///<summary>Gets the minimum SNR at which this transceiver can understand messages</summary>
	///<returns>The minimum SNR</returns>
	virtual float GetMinSNR() const override;

	UFUNCTION()
	///<summary>Sets the minimum SNR at which this transceiver can understand messages</summary>
	///<param name="NewMinSNR">The minimum SNR</param>
	virtual void SetMinSNR(const float NewMinSNR) override;

	UFUNCTION()
	///<summary>Returns the frequency this transceiver sends and receives messages on</summary>
	///<returns>The frequency</returns>
	virtual float GetFrequency() const override;

	UFUNCTION()
	///<summary>Sets the frequency this transceiver sends and receives messages on</summary>
	///<param name="NewFrequency">The new frequency to use</param>
	virtual void SetFrequency(const float NewFrequency) override;

	UFUNCTION()
	///<summary>Gets the variance of this transceiver's sending component</summary>
	///<returns>The variance</returns>
	virtual float GetVariance() const override;

	UFUNCTION()
	///<summary>Sets the variance of this transceiver's sending component</summary>
	///<param name="NewVariance">The new variance</param>
	virtual void SetVariance(const float NewVariance) override;

private:
	UPROPERTY()
	float MaxSignalStrength;
	
	UPROPERTY()
	float MinSNR;

	UPROPERTY()
	float Frequency;

	UPROPERTY()
	float Variance;


};
