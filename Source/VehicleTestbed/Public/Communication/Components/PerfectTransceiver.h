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
	UPerfectTransceiver(float aFrequency, float aMaxSignalStrength, float aMinSNR);

	void Init(float aFrequency, float aMaxSignalStrength, float aMinSNR);

public:
	virtual void Send(const IMessage& Message, float SignalStrength = 1) override;

	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const override;

	virtual void Receive(const IMessage& message, float SNR) override;

	virtual FVector GetLocation() const override;
};
