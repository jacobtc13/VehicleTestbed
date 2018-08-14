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

/*UCameraComponent * ATestbedWheeledVehicle::GetChaseCamera()
{
	return ChaseCamera;
}

UCameraComponent* ATestbedWheeledVehicle::GetInternalCamera()
{
	return InternalCamera;
}*/

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
	UE_LOG(LogTemp, Warning, TEXT("Starting character switch"));
	//TArray<AActor*> FoundActors = GetWorld()->PersistentLevel->Actors;
	int j = 0;
	//TSubclassOf<ATestbedWheeledVehicle> ClassToFind;
	if (GetLevel() == nullptr) return;
	if (GetLevel()->Actors.Num() == 0) return;
	int num = GetLevel()->Actors.Num();
	for (int i = 0; i < (GetLevel()->Actors.Num() - 1); i++)
	{
		if (GetLevel()->Actors[i]->IsA(AJackalWheeledVehicle::StaticClass()))
		{
			APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			OurPlayerController->Possess(Cast<AJackalWheeledVehicle>(GetLevel()->Actors[i]));
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Loop: %d"), i);
	}
	//int i = GetWorld()->PersistentLevel->Actors.Num();
	UE_LOG(LogTemp, Warning, TEXT("FoundActors: %d"), j);
	if (j == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No character director found"));
		return;
	}
	//ACharacterDirector* CharacterDirector = Cast<ACharacterDirector>(FoundActors[0]);
	//CharacterDirector->ChangePlayerController(IsCycleForward);k
}

void ATestbedWheeledVehicle::SwitchToOverheadCamera()
{

}

void ATestbedWheeledVehicle::SwitchToInternalCamera()
{

}

void ATestbedWheeledVehicle::SwitchToChaseCamera()
{

}