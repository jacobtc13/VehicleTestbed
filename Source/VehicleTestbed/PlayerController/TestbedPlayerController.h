#pragma once

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestbedPlayerController.generated.h"

UCLASS()
class VEHICLETESTBED_API ATestbedPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	void BeginPlay() override;

	// Pawn Swapping
private:
	TArray<AActor*> Pawns;
public:
	void SwapPawn();

	// Pausing
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PauseMenu;
private:
	UUserWidget* PauseMenuInstance;
public:
	void Pause();
};
