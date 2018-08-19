// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "DataRecorder.h"
#include "DataCollector.h"

#include "VehicleTestbedGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API AVehicleTestbedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category="Game Mode")
	UDataRecorder* dataRecorder;

public:
	///<summary>Defualt constructor for Game Mode</summary>
	AVehicleTestbedGameModeBase();

	///<summary>Called when the game starts, starts dataRecording</summary>
	virtual void BeginPlay() override;

	///<summary>Called the game ends, stops dataRecording</summary>
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
