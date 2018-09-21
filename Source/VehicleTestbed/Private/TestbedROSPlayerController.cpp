// Fill out your copyright notice in the Description page of Project Settings.

#include "TestbedROSPlayerController.h"

#include "Kismet/GameplayStatics.h"

void ATestbedROSPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	// Globally usable actions
	InputComponent->BindAction("CycleCharacterForward", EInputEvent::IE_Pressed, this, &ATestbedROSPlayerController::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &ATestbedROSPlayerController::CycleCharacterBackward);

	// Character specific actions
	/* Actions from the original player controller, replaced below with Ros Callback to Topic
	InputComponent->BindAxis("MoveForward", this, &ATestbedROSPlayerController::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &ATestbedROSPlayerController::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &ATestbedROSPlayerController::SetBrakeInput);
	*/



	InputComponent->BindAction("SwitchToOverhead", EInputEvent::IE_Pressed, this, &ATestbedROSPlayerController::SwitchToOverheadCamera);
	InputComponent->BindAction("SwitchToInternal", EInputEvent::IE_Pressed, this, &ATestbedROSPlayerController::SwitchToInternalCamera);
	InputComponent->BindAction("SwitchToChase", EInputEvent::IE_Pressed, this, &ATestbedROSPlayerController::SwitchToChaseCamera);
}

void ATestbedROSPlayerController::InitialiseRosTopic()
{
	UE_LOG(LogTemp, Log, TEXT("Beginning ROS Initialisation"), (*""));
	// Initialize a topic
	ExampleTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(this->GetWorld()->GetGameInstance());
	ExampleTopic->Init(rosinst->ROSIntegrationCore, TEXT("cmd_vel"), TEXT("geometry_msgs/Twist"));

	UE_LOG(LogTemp, Log, TEXT("ROS Topic Object Initialised"), (*""));

	// Create a std::function callback object
	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [&](TSharedPtr<FROSBaseMsg> msg) -> void
	{
		UE_LOG(LogTemp, Log, TEXT("ROS Callback"), (*""));
		auto Concrete = StaticCastSharedPtr<ROSMessages::geometry_msgs::Twist>(msg);
		if (Concrete.IsValid())
		{
			SetThrottleInput(Concrete->linear.y);
			SetSteeringInput(Concrete->angular.z);			
		}
		return;
	};
}

void ATestbedROSPlayerController::SubscribeRosTopic()
{
	// Subscribe to the topic
	ExampleTopic->Subscribe(SubscribeCallback);
	//UE_LOG(LogTemp, Log, TEXT("ROS Callback Created and Topic Subscribed"), (*""));
}

void ATestbedROSPlayerController::Tick(float DeltaTime)
{
	SubscribeRosTopic();
}

void ATestbedROSPlayerController::BeginPlay()
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
	InitialiseRosTopic();
}


void ATestbedROSPlayerController::SetThrottleInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetThrottleInput(Value);
		}
	}
}

void ATestbedROSPlayerController::SetSteeringInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetSteeringInput(Value);
		}
	}
}

void ATestbedROSPlayerController::SetBrakeInput(float Value)
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SetBrakeInput(Value);
		}
	}
}

void ATestbedROSPlayerController::SwitchToOverheadCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToOverheadCamera();
		}
	}
}

void ATestbedROSPlayerController::SwitchToInternalCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToInternalCamera();
		}
	}
}

void ATestbedROSPlayerController::SwitchToChaseCamera()
{
	if (CurrentlyPossessedPawn != nullptr)
	{
		if (CurrentlyPossessedPawn->IsA(ATestbedWheeledVehicle::StaticClass()))
		{
			Cast<ATestbedWheeledVehicle>(CurrentlyPossessedPawn)->SwitchToChaseCamera();
		}
	}
}

void ATestbedROSPlayerController::CycleCharacterForward()
{
	CycleCharacter(true);
}

void ATestbedROSPlayerController::CycleCharacterBackward()
{
	CycleCharacter(false);
}

void ATestbedROSPlayerController::CycleCharacter(bool IsCycleForward)
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



