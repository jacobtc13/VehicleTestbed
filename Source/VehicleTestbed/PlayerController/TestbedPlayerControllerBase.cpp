#include "TestbedPlayerControllerBase.h"
#include "TestbedWheeledVehicle.h"


void ATestbedPlayerControllerBase::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	// Pawn Swapping
	InputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &ATestbedPlayerControllerBase::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &ATestbedPlayerControllerBase::CycleCharacterBackward);
	
	// Pausing
	InputComponent->BindAction("PauseButton", IE_Released, this, &ATestbedPlayerControllerBase::Pause);
}

void ATestbedPlayerControllerBase::BeginPlay()
{
	APlayerController::BeginPlay();

	// Pawn Swapping
	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), ControllablePawns);
	if (this->GetPawn() != nullptr)
	{
		CurrentPawnIndex = ControllablePawns.Find(this->GetPawn());
	}
	else
	{
		CurrentPawnIndex = 0;
	}

	// Pausing
	PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenu);
}

// Pawn Swapping
void ATestbedPlayerControllerBase::CycleCharacterForward()
{
	CycleCharacter(true);
}

void ATestbedPlayerControllerBase::CycleCharacterBackward()
{
	CycleCharacter(false);
}

void ATestbedPlayerControllerBase::CycleCharacter(bool IsCycleForward)
{
	// TODO: Once the actor is switched, the controller will need to be replaced with an AI controller

	// Returns if the level is null or there are less than 2 actors to choose from
	if (ControllablePawns.Num() < 2) return;

	if (IsCycleForward)
	{
		if (!ControllablePawns.IsValidIndex(++CurrentPawnIndex))
		{
			CurrentPawnIndex = 0;
		}
	}
	else
	{
		if (!ControllablePawns.IsValidIndex(--CurrentPawnIndex))
		{
			CurrentPawnIndex = ControllablePawns.Num() - 1;
		}
	}
	Possess((APawn*)ControllablePawns[CurrentPawnIndex]);
}

/*void ATestbedPlayerControllerBase::SwapPawn()
{
	int32 index = Pawns.Find(GetPawn());
	if (!Pawns.IsValidIndex(++index))
		index = 0;
	Possess((APawn*)Pawns[index]);
}*/

// Pausing
void ATestbedPlayerControllerBase::Pause()
{
	PauseMenuInstance->AddToViewport();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	SetPause(true);
}
