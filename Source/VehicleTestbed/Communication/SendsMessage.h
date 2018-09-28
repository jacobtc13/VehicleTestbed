#pragma once

#include "TranceiverBase.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SendsMessage.generated.h"

UINTERFACE(MinimalAPI)
class USendsMessage : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API ISendsMessage : public ITranceiverBase
{
	GENERATED_BODY()

public:
	virtual void Initialization(float aFrequency, float aMaxSignalStrength);

	virtual void Send(const IMessage& Message, float SignalStrength = 1) = 0;

	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const = 0;

	virtual void ChangeFrequency(const float& NewFrequency);

protected:
	float Frequency;
	float MaxSignalStrength;

private:
	//TODO Add friend methods from CommunicationDistributor
	//friend void CommunicationDistributor::Send();
};
