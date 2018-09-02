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

	UFUNCTION()
	///<summary>Switches to the next available vehicle in the array</summary>
	void CycleCharacterForward();

	UFUNCTION()
	///<summary>Switches to the previous available vehicle in the array</summary>
	void CycleCharacterBackward();

	UFUNCTION()
	///<summary>Sets the current forward movement applied to the pawn by the player</summary>
	///<param name='Value'>Value of the movement applied</param>  
	void SetThrottleInput(float Value);

	UFUNCTION()
	///<summary>Sets the steering/strafing direction and magnitude of it to the pawn</summary>
	///<param name='Value'>Value of the steering/strafing applied, positive and negative give steering direction (+ is right)</param>  
	void SetSteeringInput(float Value);

	UFUNCTION()
	///<summary>Sets the current braking applied to the vehicle by the player</summary>
	///<param name='Value'>Value of the brakes applied</param>  
	void SetBrakeInput(float Value);

	UFUNCTION()
	///<summary>Gets overhead view for the pawn</summary>
	void SwitchToOverheadCamera();

	UFUNCTION()
	///<summary>Gets first person view camera for the pawn</summary>
	void SwitchToInternalCamera();

	UFUNCTION()
	///<summary>Gets third person view camera for the pawn</summary>
	void SwitchToChaseCamera();

protected:
	///<summary>Allows the PlayerController to set up custom input bindings</summary>
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TArray<AActor*> ControllablePawns;

	int32 CurrentPawnIndex;

	UPROPERTY()
	APawn* CurrentlyPossessedPawn = nullptr;

	UFUNCTION()
	///<summary>Cycles through the list of current actors to control</summary>
	///<param name='IsCycleForward'>Is the character being changed to the next one in the list?</param>  
	void CycleCharacter(bool IsCycleForward);
};
