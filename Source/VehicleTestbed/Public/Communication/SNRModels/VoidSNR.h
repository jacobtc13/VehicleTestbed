#pragma once

#include "SNRModel.h"
#include "CoreMinimal.h"
#include "VoidSNR.generated.h"

UCLASS()
class UVoidSNR : public USNRModel
{
	GENERATED_BODY()

public:
	///<summary>Always returns a 0 SNR</summary>
	float CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const override;
};
