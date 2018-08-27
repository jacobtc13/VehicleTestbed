#include "TestbedPlayerController.h"
#include "TestbedWheeledVehicle.h"


void ATestbedPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	// Pawn Swapping
	InputComponent->BindAction("SwitchCamera", IE_Released, this, &ATestbedPlayerController::SwapPawn);
	// Pausing
	InputComponent->BindAction("PauseButton", IE_Released, this, &ATestbedPlayerController::Pause);
}

void ATestbedPlayerController::BeginPlay()
{
	APlayerController::BeginPlay();

	// Pawn Swapping
	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), Pawns);
	// Pausing
	PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenu);
}

// Pawn Swapping
void ATestbedPlayerController::SwapPawn()
{
	int32 index = Pawns.Find(GetPawn());
	if (!Pawns.IsValidIndex(++index))
		index = 0;
	Possess((APawn*)Pawns[index]);
}

// Pausing
void ATestbedPlayerController::Pause()
{
	PauseMenuInstance->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SetPause(true);
}
