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
	virtual void Send(const IMessage& Message, float SignalStrength) = 0;
	virtual void CalculatePower(float transmissionPower, float targetFrequency, float actualFrequency) = 0;

	virtual const float GetFrequency() const;
	virtual void SetFrequency(const float& NewFrequency);

protected:
	float frequency;
	float maxSignalStrength;

private:
	//TODO Add friend methods from CommunicationDistributor
	//friend void CommunicationDistributor::Send();
};
