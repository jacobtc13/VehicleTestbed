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
	USNRModel* Model;

public:
	USNRModelFrequencyRange();

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the minimum frequency of this range</summary>
	///<param name="NewMin">The new minimum frequency</param>
	void SetMinFrequency(float NewMin);

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the minimum frequency of this range</summary>
	///<returns>The minimum frequency</returns>
	float GetMinFrequency() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the maximum frequency of this range</summary>
	///<param name="NewMax">Thew new maximum frequency</param>
	void SetMaxFrequency(float NewMax);

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the maximum frequency of this range</summary>
	///<returns>The maximum frequency</returns>
	float GetMaxFrequency() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the SNR model for this range</summary>
	///<param name="NewSNR">The new SNR model</param>
	void SetSNRModel(USNRModel* NewSNR);

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the SNR model of this range</summary>
	///<returns>The SNR model</returns>
	USNRModel* GetSNRModel() const;
};
