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
	
public:
	///<summary>Event that is called when play begins for this actor</summary>
	virtual void BeginPlay() override;

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the next available vehicle in the array</summary>
	void CycleCharacterForward();

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the previous available vehicle in the array</summary>
	void CycleCharacterBackward();

protected:
	///<summary>Allows the PlayerController to set up custom input bindings</summary>
	virtual void SetupInputComponent() override;

private:
	TArray<AActor*> ControllablePawns;

	int32 CurrentPawnIndex;

	UFUNCTION()
	///<summary>Cycles through the list of current actors to control</summary>
	///<param name='IsCycleForward'>Is the character being changed to the next one in the list?</param>  
	void CycleCharacter(bool IsCycleForward);
};
