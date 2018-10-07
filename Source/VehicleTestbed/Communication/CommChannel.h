// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <list>
#include "MessageReceiver.h"
#include "SNRModel.h"
#include "CommChannel.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommChannel : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VEHICLETESTBED_API ICommChannel
{
	//GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
private:
	float frequency;
	TArray<UMessageReceiver> receivers;
	ISNRModel snrModel;

public:
	ICommChannel(float);
	float GetFrequency();
	void AddReceivers(TArray <UMessageReceiver>);
	
	
};
