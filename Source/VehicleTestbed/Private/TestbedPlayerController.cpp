// Fill out your copyright notice in the Description page of Project Settings.

#include "TestbedPlayerController.h"
#include "TestbedWheeledVehicle.h"
#include "GameFramework/SpectatorPawn.h"

#include "Kismet/GameplayStatics.h"


void ATestbedPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	// Globally usable actions
	InputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::CycleCharacterBackward);

	// Character specific actions
	InputComponent->BindAxis("MoveForward", this, &ATestbedPlayerController::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &ATestbedPlayerController::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &ATestbedPlayerController::SetBrakeInput);
	InputComponent->BindAction("SwitchToOverhead", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::SwitchToOverheadCamera);
	InputComponent->BindAction("SwitchToInternal", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::SwitchToInternalCamera);
	InputComponent->BindAction("SwitchToChase", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::SwitchToChaseCamera);
}
void ATestbedPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), ControllablePawns);
	if (this->GetPawn() != nullptr)
	{
		CurrentlyPossessedPawn = this->GetPawn();
		CurrentPawnIndex = ControllablePawns.Find(CurrentlyPossessedPawn);
	}
	else
	{
		CurrentPawnIndex = 0;
	}
}


void ATestbedPlayerController::SetThrottleInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetThrottleInput(Value);
		}
	}
}

void ATestbedPlayerController::SetSteeringInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetSteeringInput(Value);
		}
	}
}

void ATestbedPlayerController::SetBrakeInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetBrakeInput(Value);
		}
	}
}

void ATestbedPlayerController::SwitchToOverheadCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToOverheadCamera();
		}
	}
}

void ATestbedPlayerController::SwitchToInternalCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToInternalCamera();
		}
	}
}

void ATestbedPlayerController::SwitchToChaseCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToChaseCamera();
		}
	}
}

void ATestbedPlayerController::CycleCharacterForward()
{
	CycleCharacter(true);
}

void ATestbedPlayerController::CycleCharacterBackward()
{
	CycleCharacter(false);
}

void ATestbedPlayerController::CycleCharacter(bool IsCycleForward)
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
		CurrentlyPossessedPawn = Cast<APawn>(ControllablePawns[CurrentPawnIndex]);
	}
	else
	{
		if (!ControllablePawns.IsValidIndex(--CurrentPawnIndex))
		{
			CurrentPawnIndex = ControllablePawns.Num() - 1;
		}
		CurrentlyPossessedPawn = Cast<APawn>(ControllablePawns[CurrentPawnIndex]);
	}
	Possess((APawn*)ControllablePawns[CurrentPawnIndex]);
}
