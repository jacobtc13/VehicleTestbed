#pragma once

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerComponent/PCComponent.h"
#include "JackalControlComponent.generated.h"

UCLASS()
class UJackalControlComponent : public UPCComponent
{
	GENERATED_BODY()

public:
	///<summary>Binds the actions of driving and changing cameras of the Jackal</summary>
	///<param name="inputComponent">The input component of the player controller this component is part of</param>
	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	///<summary>Called automatically by Unreal.  Sets up a list of all the pawns in the game world.</summary>
	void BeginPlay() override;

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
};
