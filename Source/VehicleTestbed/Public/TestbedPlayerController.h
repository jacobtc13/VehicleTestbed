// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestbedWheeledVehicle.h"

#include "TestbedPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API ATestbedPlayerController : public APlayerController
{
	GENERATED_BODY()

	void SetupInputComponent();
	
	void BeginPlay();

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the next available vehicle in the array</summary>
	void CycleCharacterForward();

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the previous available vehicle in the array</summary>
	void CycleCharacterBackward();

private:
	TArray<AActor*> ControllablePawns;

	int32 CurrentPawnIndex;

	UFUNCTION()
	///<summary>Cycles through the list of current actors to control</summary>
	///<param name='IsCycleForward'>Is the character being changed to the next one in the list?</param>  
	void CycleCharacter(bool IsCycleForward);
};
