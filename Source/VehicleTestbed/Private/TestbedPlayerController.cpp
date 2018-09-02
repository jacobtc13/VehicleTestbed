// Fill out your copyright notice in the Description page of Project Settings.

#include "TestbedPlayerController.h"
#include "GameFramework/SpectatorPawn.h"

#include "Kismet/GameplayStatics.h"


void ATestbedPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &ATestbedPlayerController::CycleCharacterBackward);
}
void ATestbedPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), ControllablePawns);
	if (this->GetPawn() != nullptr)
	{
		CurrentPawnIndex = ControllablePawns.Find(this->GetPawn());
	}
	else
	{
		CurrentPawnIndex = 0;
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
