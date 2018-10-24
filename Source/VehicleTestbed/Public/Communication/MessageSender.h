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
	virtual void Initialization(float aFrequency, float aMaxSignalStrength);

	virtual void Send(const IMessage& Message, float SignalStrength = 1);

	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const = 0;

	virtual void ChangeFrequency(const float& NewFrequency);

	virtual float GetFrequency() const;
	virtual void SetFrequency(const float& NewFrequency);

protected:
	float Frequency;
	float MaxSignalStrength;

private:
	//TODO Add friend methods from CommunicationDistributor
	//friend void CommunicationDistributor::Send();
};
