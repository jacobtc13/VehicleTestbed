// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "JackalMovementComponent.h"
#include "JackalVehicle.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API AJackalVehicle : public AWheeledVehicle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AJackalVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//class UJackalMovementComponent* OurMovementComponent;

	//virtual UPawnMovementComponent* GetMovementComponent() const override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);

	UFUNCTION(Category = "Jackal Vehicle", BlueprintCallable)
		void SetThrottleInput(float Value);

	UFUNCTION(Category = "Jackal Vehicle", BlueprintCallable)
		void SetSteeringInput(float Value);

	UFUNCTION(Category = "Jackal Vehicle", BlueprintCallable)
		void SetBrakeInput(float Value);

	UFUNCTION(Category = "Jackal Vehicle", BlueprintCallable)
		void SetReverse(bool Value);
};




/*UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
USpringArmComponent *SpringArm;

UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
UCameraComponent *Camera3rdPerson;

UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
UCameraComponent *Camera1stPerson;*/