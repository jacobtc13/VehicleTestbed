// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WheeledVehicle.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "TestbedWheeledVehicle.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API ATestbedWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	//////////////////////////////
	//Constructor/Deconstructor//
	////////////////////////////

	ATestbedWheeledVehicle();
	
	~ATestbedWheeledVehicle();

	/////////////////////
	// Vehicle Control//
	///////////////////

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
		void SetThrottleInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
		void SetSteeringInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
		void SetBrakeInput(float Value);

	///////////////////
	// Get functions//
	/////////////////

	/// Forward speed in km/h. Might be negative if goes backwards.
	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
		float GetVehicleForwardSpeed() const;

protected:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* ChaseCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* InternalCamera;
};
