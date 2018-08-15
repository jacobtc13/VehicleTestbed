#include "TestbedWheeledVehicle.h"

#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"
#include "JackalWheeledVehicle.h"

#include "WheeledVehicleMovementComponent.h"
#include "CoreMinimal.h"

ATestbedWheeledVehicle::ATestbedWheeledVehicle()
{
	// All camera position values need to be manually changed based on size of vehicle in inherited classes.
	// Use a spring arm to give the camera smooth, natural-feeling motion.
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);

	// Create a camera and attach to our spring arm
	ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ChaseCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	// Create internal camera for viewing from inside vehicle
	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	InternalCamera->SetupAttachment(RootComponent);

	// Create overhead camera for viewing from above the vehicle
	OverheadCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OverheadCamera"));
	OverheadCamera->SetupAttachment(RootComponent);

	ActiveCamera = ChaseCamera;
	ActiveCamera->Activate();
}

ATestbedWheeledVehicle::~ATestbedWheeledVehicle()
{

}

void ATestbedWheeledVehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Binds actions to player input which are based on the functions in UE under Project Settings->Input
	InputComponent->BindAxis("MoveForward", this, &ATestbedWheeledVehicle::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &ATestbedWheeledVehicle::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &ATestbedWheeledVehicle::SetBrakeInput);
	InputComponent->BindAction("CycleVehicleForward", EInputEvent::IE_Pressed, this, &ATestbedWheeledVehicle::CycleCharacterForward);
	InputComponent->BindAction("CycleCharacterBackward", EInputEvent::IE_Pressed, this, &ATestbedWheeledVehicle::CycleCharacterBackward);
	InputComponent->BindAction("SwitchToOverhead", EInputEvent::IE_Pressed, this, &ATestbedWheeledVehicle::SwitchToOverheadCamera);
	InputComponent->BindAction("SwitchToInternal", EInputEvent::IE_Pressed, this, &ATestbedWheeledVehicle::SwitchToInternalCamera);
	InputComponent->BindAction("SwitchToChase", EInputEvent::IE_Pressed, this, &ATestbedWheeledVehicle::SwitchToChaseCamera);
}

void ATestbedWheeledVehicle::SetThrottleInput(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void ATestbedWheeledVehicle::SetSteeringInput(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void ATestbedWheeledVehicle::SetBrakeInput(float Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value);
}

float ATestbedWheeledVehicle::GetVehicleForwardSpeed() const
{
	// Conversion is done to output result in km/h
	return GetVehicleMovementComponent()->GetForwardSpeed() * 0.036f;
}

void ATestbedWheeledVehicle::CycleCharacterForward()
{
	CycleCharacter(true);
}

void ATestbedWheeledVehicle::CycleCharacterBackward()
{
	CycleCharacter(false);
}

void ATestbedWheeledVehicle::CycleCharacter(bool IsCycleForward)
{
	// TODO: This entire function needs to be placed in the game mode where references to all actors that can be cycled through will be stored
	// TODO: Once the actor is switched, the controller will need to be replaced with an AI controller
	// Returns if the level is null or there are less than 2 actors to choose from
	if (GetLevel() == nullptr) return;
	if (GetLevel()->Actors.Num() <= 1) return; // TODO: Read from list of possessable actors instead
	int num = GetLevel()->Actors.Num();
	for (int i = 0; i < (GetLevel()->Actors.Num()); i++)
	{
		// Temporary action: Loop through actors and possess the next available testbedvehicleclass that isn't the current
		// When moved to the GameMode, will cycle through list of possessable vehicles instead
		if (GetLevel()->Actors[i]->IsA(ATestbedWheeledVehicle::StaticClass()) && GetLevel()->Actors[i] != this)
		{
			APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			OurPlayerController->Possess(Cast<AJackalWheeledVehicle>(GetLevel()->Actors[i]));
			UE_LOG(LogTemp, Warning, TEXT("Changing vehicle"));
			return;
		}
	}
}

void ATestbedWheeledVehicle::SwitchToOverheadCamera()
{
	SwitchActiveCamera(OverheadCamera);
}

void ATestbedWheeledVehicle::SwitchToInternalCamera()
{
	SwitchActiveCamera(InternalCamera);
}

void ATestbedWheeledVehicle::SwitchToChaseCamera()
{
	SwitchActiveCamera(ChaseCamera);
}

void ATestbedWheeledVehicle::SwitchActiveCamera(UCameraComponent* NewActiveCamera)
{
	ActiveCamera->Deactivate();
	ActiveCamera = NewActiveCamera;
	ActiveCamera->Activate();
}