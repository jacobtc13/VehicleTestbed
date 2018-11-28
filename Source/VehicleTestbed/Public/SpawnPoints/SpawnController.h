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
* CONTROLLER CLASS FOR UPDATING SPAWN LOCATION - MAY NOT BE NEEDED
*/
UCLASS()
class VEHICLETESTBED_API USpawnController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	///<summary>Returns an Array of FNames representing all SpawnPoints</summary>
	///<returns><see cref="TArray"> Returns a TArray of FNames</returns> 
	TArray<FName> GetSpawnPointRefs() const;

private:
	SpawnPointList spList;
};

