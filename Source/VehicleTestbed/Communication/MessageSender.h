#pragma once

#include "CoreMinimal.h"
#include "Communication/Messager.h"
#include "MessageSender.generated.h"

UCLASS()
class VEHICLETESTBED_API UMessageSender : public UMessager
{
	GENERATED_BODY()

public:
	UMessageSender()
		: UMessager()
	{
		maxSignalStrength = 100;
	}

	UMessageSender(float aMaxSignalStrength);

	template <class Message>
	void Send(Message message, float signalStrength)
	{

	}

private:
	float frequency;
	float freqVariance;
	float maxSignalStrength;
};
