// Fill out your copyright notice in the Description page of Project Settings.

#include "TestbedWheeledVehicle.h"

#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"

#include "WheeledVehicleMovementComponent.h"
#include "CoreMinimal.h"

ATestbedWheeledVehicle::ATestbedWheeledVehicle()
{
	// Use a spring arm to give the camera smooth, natural-feeling motion.
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->RelativeRotation = FRotator(-20.f, 0.f, 0.f);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ChaseCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	// Create internal camera for viewing from inside vehicle
	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	InternalCamera->SetupAttachment(RootComponent);
}

ATestbedWheeledVehicle::~ATestbedWheeledVehicle()
{

}

/////////////////////
// Vehicle Control//
///////////////////

void ATestbedWheeledVehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ATestbedWheeledVehicle::SetThrottleInput);
	InputComponent->BindAxis("MoveRight", this, &ATestbedWheeledVehicle::SetSteeringInput);
	InputComponent->BindAxis("Brake", this, &ATestbedWheeledVehicle::SetBrakeInput);
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

///////////////////
// Get functions//
/////////////////

float ATestbedWheeledVehicle::GetVehicleForwardSpeed() const
{
	return GetVehicleMovementComponent()->GetForwardSpeed() * 0.036f;
}

