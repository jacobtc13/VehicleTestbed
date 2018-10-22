#pragma once

#include "CoreMinimal.h"
#include "SNRModel.h"
#include "SNRModelFrequencyRange.generated.h"

UCLASS()
class USNRModelFrequencyRange : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintSetter=SetMinFrequency, BlueprintGetter=GetMinFrequency)
	float MinFrequency;
	UPROPERTY(BlueprintSetter=SetMaxFrequency, BlueprintGetter=GetMaxFrequency)
	float MaxFrequency;
	UPROPERTY(BlueprintSetter=SetSNRModel, BlueprintGetter=GetSNRModel)
	ISNRModel* Model;

public:
	USNRModelFrequencyRange();

	UFUNCTION(BlueprintSetter)
	void SetMinFrequency(float NewMin);
	UFUNCTION(BlueprintGetter)
	float GetMinFrequency() const;

	UFUNCTION(BlueprintSetter)
	void SetMaxFrequency(float NewMax);
	UFUNCTION(BlueprintGetter)
	float GetMaxFrequency() const;

	UFUNCTION(BlueprintSetter)
	void SetSNRModel(ISNRModel* NewSNR);
	UFUNCTION(BlueprintGetter)
	ISNRModel* GetSNRModel() const;
};
