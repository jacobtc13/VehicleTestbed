// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MessageSender.h"
#include "MessageReceiver.h"
#include "SNRModel.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USNRModel : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VEHICLETESTBED_API ISNRModel
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	float CalculateSNR(UMessageSender sender, UMessageReceiver receiver);
	
};
