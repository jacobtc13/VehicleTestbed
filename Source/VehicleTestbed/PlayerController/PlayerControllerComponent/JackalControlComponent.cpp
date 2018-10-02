#include "JackalControlComponent.h"
#include "GameFramework/Pawn.h"
#include "TestbedWheeledVehicle.h"

void UJackalControlComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &UJackalControlComponent::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &UJackalControlComponent::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &UJackalControlComponent::SetBrakeInput);
	InputComponent->BindAction("SwitchToOverhead", EInputEvent::IE_Pressed, this, &UJackalControlComponent::SwitchToOverheadCamera);
	InputComponent->BindAction("SwitchToInternal", EInputEvent::IE_Pressed, this, &UJackalControlComponent::SwitchToInternalCamera);
	InputComponent->BindAction("SwitchToChase", EInputEvent::IE_Pressed, this, &UJackalControlComponent::SwitchToChaseCamera);
}

void UJackalControlComponent::BeginPlay()
{
	UPCComponent::BeginPlay();
}

void UJackalControlComponent::SetThrottleInput(float Value)
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetThrottleInput(Value);
		}
	}
}

void UJackalControlComponent::SetSteeringInput(float Value)
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetSteeringInput(Value);
		}
	}
}

void UJackalControlComponent::SetBrakeInput(float Value)
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetBrakeInput(Value);
		}
	}
}

void UJackalControlComponent::SwitchToOverheadCamera()
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToOverheadCamera();
		}
	}
}

void UJackalControlComponent::SwitchToInternalCamera()
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToInternalCamera();
		}
	}
}

void UJackalControlComponent::SwitchToChaseCamera()
{
	APawn* CurrentlyPossessedPawn = Controller->GetPawn();
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToChaseCamera();
		}
	}
}
