#include "TestbedPlayerController.h"
#include "DemoTransceiverControllerComponent.h"

ATestbedPlayerController::ATestbedPlayerController()
	: APlayerController()
{
	PauseMenuComponent = CreateDefaultSubobject<UPauseMenuComponent>("PauseMenuComponent");
	PawnSwapComponent = CreateDefaultSubobject<UPawnSwapComponent>("PawnSwapComponent");
	JackalControlComponent = CreateDefaultSubobject<UJackalControlComponent>("JackalControlComponent");
	TransceiverControllerComponent = CreateDefaultSubobject<UDemoTransceiverControllerComponent>("TransceiverControllerComponent");
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
