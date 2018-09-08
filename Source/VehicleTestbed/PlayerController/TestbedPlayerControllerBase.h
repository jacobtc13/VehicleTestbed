#pragma once

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestbedPlayerControllerBase.generated.h"

UCLASS()
class VEHICLETESTBED_API ATestbedPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	///<summary>Allows the PlayerController to set up custom input bindings</summary>
	virtual void SetupInputComponent() override;

	///<summary>Event that is called when play begins for this actor</summary>
	virtual void BeginPlay() override;

	// Pawn Swapping
	UFUNCTION(Category="Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the next available vehicle in the array</summary>
	void CycleCharacterForward();

	UFUNCTION(Category="Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Switches to the previous available vehicle in the array</summary>
	void CycleCharacterBackward();

	// Pausing
	///<summary>Adds the pause widget to the screen and pauses the game</summary>
	void Pause();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PauseMenu;

private:
	// Pawn Swapping
	TArray<AActor*> ControllablePawns;

	int32 CurrentPawnIndex;

	UFUNCTION()
	///<summary>Cycles through the list of current actors to control</summary>
	///<param name='IsCycleForward'>Is the character being changed to the next one in the list?</param>  
	void CycleCharacter(bool IsCycleForward);

	// Pausing
	UPROPERTY()
	UUserWidget* PauseMenuInstance;
};
