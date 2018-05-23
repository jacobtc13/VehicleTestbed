// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalVehicle.h"
#include "JackalMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

AJackalVehicle::AJackalVehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AJackalVehicle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AJackalVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJackalVehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AJackalVehicle::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &AJackalVehicle::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &AJackalVehicle::SetBrakeInput);
}

/*UPawnMovementComponent* AJackalVehicle::GetMovementComponent() const
{
	return OurMovementComponent;
}*/

/*void AJackalVehicle::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void AJackalVehicle::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void AJackalVehicle::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}*/

void AJackalVehicle::SetThrottleInput(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void AJackalVehicle::SetSteeringInput(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void AJackalVehicle::SetBrakeInput(float Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value);
}

void AJackalVehicle::SetReverse(bool Value)
{
}


