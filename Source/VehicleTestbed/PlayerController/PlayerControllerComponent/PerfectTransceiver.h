#pragma once

#include "Communication/SendsMessage.h"
#include "Communication/ReceivesMessage.h"

#include "CoreMinimal.h"
#include "PCComponent.h"
#include "PerfectTransceiver.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETESTBED_API UPerfectTransceiver : public UPCComponent, public ISendsMessage, public IReceivesMessage
{
	GENERATED_BODY()

public:
	UPerfectTransceiver();
	UPerfectTransceiver(float aFrequency, float aMaxSignalStrength, float aMinSNR);

	void Init(float aFrequency, float aMaxSignalStrength, float aMinSNR);

public:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Send(const IMessage& Message, float SignalStrength = 1) override;

	virtual float CalculatePower(float TransmissionPower, float TargetFrequency, float ActualFrequency) const override;

	virtual void Receive(const IMessage& message, float SNR) override;

	virtual FVector GetLocation() const override;
};
