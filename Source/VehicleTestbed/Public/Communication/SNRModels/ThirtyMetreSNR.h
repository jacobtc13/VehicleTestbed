#pragma once

#include "SNRModel.h"
#include "CoreMinimal.h"
#include "ThirtyMetreSNR.generated.h"

UCLASS()
class UThirtyMetreSNR : public USNRModel
{
	GENERATED_BODY()

public:
	///<summary>Returns the signal strength of the message if within 30 metres or 0 beyond</summary>
	float CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const override;
};
