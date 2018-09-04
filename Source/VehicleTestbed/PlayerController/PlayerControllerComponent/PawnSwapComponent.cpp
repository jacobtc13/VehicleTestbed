#include "PawnSwapComponent.h"

void UPawnSwapComponent::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	check(inputComponent);
	inputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &UPawnSwapComponent::CycleCharacterForward);
	inputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &UPawnSwapComponent::CycleCharacterBackward);
}

void UPawnSwapComponent::BeginPlay()
{
	UPCComponent::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), APawn::StaticClass(), ControllablePawns);
	if (controller->GetPawn() != nullptr)
	{
		CurrentPawnIndex = ControllablePawns.Find(controller->GetPawn());
	}
	else
	{
		CurrentPawnIndex = 0;
	}
}

void UPawnSwapComponent::CycleCharacterForward()
{
	CycleCharacter(true);
}

void UPawnSwapComponent::CycleCharacterBackward()
{
	CycleCharacter(false);
}

void UPawnSwapComponent::CycleCharacter(bool IsCycleForward)
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
	controller->Possess((APawn*)ControllablePawns[CurrentPawnIndex]);
}
