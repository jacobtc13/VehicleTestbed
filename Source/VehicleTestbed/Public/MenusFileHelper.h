// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MenusFileHelper.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API UMenusFileHelper : public UObject
{
	GENERATED_BODY()

	TArray<FString> FileNames(FString directory);

	TArray<FString> MapNames();
};
