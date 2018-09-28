#pragma once

#include "SendsMessage.h"
#include "ReceivesMessage.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerfectTransceiver.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETESTBED_API UPerfectTransceiver : public UActorComponent, public virtual ISendsMessage, public virtual IReceivesMessage
{
	GENERATED_BODY()

public:
	UPerfectTransceiver();
	void Initialization(float aFrequency, float aMaxSignalStrength, float aMinSNR);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Send(const IMessage& Message, float SignalStrength = 1) override;

	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const override;

	virtual void Receive(const IMessage& message, float SNR) override;

	virtual FVector GetLocation() const override;
};
