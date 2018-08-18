#include "TestPlayerController.h"
#include "TestbedWheeledVehicle.h"
#include "Blueprint/UserWidget.h"


void ATestPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	// Pawn Swapping
	InputComponent->BindAction("SwitchCamera", IE_Released, this, &ATestPlayerController::SwapPawn);
	// Pausing
	InputComponent->BindAction("PauseButton", IE_Released, this, &ATestPlayerController::Pause);
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Pawn Swapping
	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), Pawns);
	// Pausing
	PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenu);
}

// Pawn Swapping
void ATestPlayerController::SwapPawn()
{
	int32 index = Pawns.Find(GetPawn());
	if (!Pawns.IsValidIndex(++index))
		index = 0;
	Possess((APawn*)Pawns[index]);
}

// Pausing
void ATestPlayerController::Pause()
{
	PauseMenuInstance->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SetPause(true);
}
