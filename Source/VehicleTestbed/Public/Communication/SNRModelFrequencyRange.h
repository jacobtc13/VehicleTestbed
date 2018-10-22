// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SNRModel.h"
#include "SNRModelFrequencyRange.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USNRModelFrequencyRange : public UInterface
{
	//GENERATED_BODY()
};

/**
 * 
 */
class VEHICLETESTBED_API ISNRModelFrequencyRange
{
	//GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
private:
	float minFrequency, maxFrequency;
	ISNRModel model;
public:
	void SetMinFrequency(float);
	float GetMinFrequency();

	void SetMaxFrequency(float);
	float GetMaxFrequency();

	void SetSNRModel(ISNRModel);
	ISNRModel GetSNRModel();
}; 