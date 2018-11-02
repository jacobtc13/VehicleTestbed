#pragma once

#include "SNRModel.h"
#include "CoreMinimal.h"
#include "ThirtyMetreSNR.generated.h"

UCLASS()
class UThirtyMetreSNR : public USNRModel
{
	GENERATED_BODY()

public:
	float CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const override;
};
