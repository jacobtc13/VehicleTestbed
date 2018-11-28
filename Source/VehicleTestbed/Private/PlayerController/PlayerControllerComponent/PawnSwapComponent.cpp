#include "PawnSwapComponent.h"
#include "TestbedWheeledVehicle.h"

void UPawnSwapComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &UPawnSwapComponent::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &UPawnSwapComponent::CycleCharacterBackward);
}

void UPawnSwapComponent::BeginPlay()
{
	UPCComponent::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), ATestbedWheeledVehicle::StaticClass(), ControllablePawns);
	if (Controller->GetPawn() != nullptr)
	{
		CurrentPawnIndex = ControllablePawns.Find(Controller->GetPawn());
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

void UPawnSwapComponent::CycleCharacter(bool bIsCycleForward)
{
	// TODO: Once the actor is switched, the controller will need to be replaced with an AI controller

	// Returns if the level is null or there are less than 2 actors to choose from
	if (ControllablePawns.Num() < 2) return;

	if (bIsCycleForward)
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
	Controller->Possess((APawn*)ControllablePawns[CurrentPawnIndex]);
}
