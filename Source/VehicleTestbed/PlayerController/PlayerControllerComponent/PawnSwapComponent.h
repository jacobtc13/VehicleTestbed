#pragma once

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerComponent/PCComponent.h"
#include "PawnSwapComponent.generated.h"

UCLASS()
class VEHICLETESTBED_API UPawnSwapComponent : public UPCComponent
{
	GENERATED_BODY()

public:
	///<summary>Binds the actions of cycling forward and backward between pawns</summary>
	///<param name="inputComponent">The input component of the player controller this component is part of</param>
	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	///<summary>Called automatically by Unreal.  Sets up a list of all the pawns in the game world.</summary>
	void BeginPlay() override;

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
