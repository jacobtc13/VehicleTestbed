#include "TestbedPlayerController.h"

ATestbedPlayerController::ATestbedPlayerController()
	: APlayerController()
{
	pauseMenuComponent = CreateDefaultSubobject<UPauseMenuComponent>("PauseMenuComponent");
	pawnSwapComponent = CreateDefaultSubobject<UPawnSwapComponent>("PawnSwapComponent");
}

void ATestbedPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	pauseMenuComponent->SetupPlayerInputComponent(InputComponent);
	pawnSwapComponent->SetupPlayerInputComponent(InputComponent);
}

void ATestbedPlayerController::BeginPlay()
{
	APlayerController::BeginPlay();
}
