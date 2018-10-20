// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array.h"
#include "SpawnPoint.h"
#include "VehicleTestbed.h""
#include "UObject.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"


/**
 * 
 */
class VEHICLETESTBED_API SpawnPointList
{

private:
	TArray<SpawnPoint> spList;
	UWorld* const World;

public:
	
	SpawnPointList();

	~SpawnPointList();
};
