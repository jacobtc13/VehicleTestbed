#include "TestbedPlayerController.h"

ATestbedPlayerController::ATestbedPlayerController()
	: APlayerController()
{
	PauseMenuComponent = CreateDefaultSubobject<UPauseMenuComponent>("PauseMenuComponent");
	PawnSwapComponent = CreateDefaultSubobject<UPawnSwapComponent>("PawnSwapComponent");
	JackalControlComponent = CreateDefaultSubobject<UJackalControlComponent>("JackalControlComponent");
}

void ATestbedPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	PauseMenuComponent->SetupPlayerInputComponent(InputComponent);
	PawnSwapComponent->SetupPlayerInputComponent(InputComponent);
	JackalControlComponent->SetupPlayerInputComponent(InputComponent);
}

void ATestbedPlayerController::BeginPlay()
{
	APlayerController::BeginPlay();
}
