#pragma once

#include "TranceiverBase.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MessageReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UMessageReceiver : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API IMessageReceiver : public ITranceiverBase
{
	GENERATED_BODY()

public:
	virtual void Receive(const IMessage& message, float SNR) = 0;

	virtual void Initialization(float aMinSNR);

	enum EResponseCode
	{
		Received,
		Garbled
	};

	float GetFrequency() const;
	void SetFrequency(const float NewFrequency);

protected:
	float Frequency;
	float MinSNR;
};
