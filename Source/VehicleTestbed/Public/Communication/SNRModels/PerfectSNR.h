#pragma once

#include "SNRModel.h"
#include "CoreMinimal.h"
#include "PerfectSNR.generated.h"

UCLASS()
class UPerfectSNR : public USNRModel
{
	GENERATED_BODY()

public:
	///<summary>Allows all messages to get through. Implies a 0 noise environment.</summary>
	float CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const override;
};