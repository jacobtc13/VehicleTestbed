// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Array.h"
#include "SpawnPoint.h"
#include "SpawnPointList.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "SpawnPointList.h"
#include "SpawnPoint.h"
#include "SpawnController.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API USpawnController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	TArray<FName> getSpawnPointRefs();

	
};

