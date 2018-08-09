#pragma once

#include "WheeledVehicle.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "TestbedWheeledVehicle.generated.h"

UCLASS()
///<summary>Base class for all wheeled vehicle actors. Sets up cameras and controls for player usage.</summary>
class VEHICLETESTBED_API ATestbedWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	ATestbedWheeledVehicle();
	
	~ATestbedWheeledVehicle();

	///<summary>Sets up the player input controls</summary>
	///<param name='InputComponent'>Player input control that will have actions of the vehicle bound to it</param>  
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Sets the current throttle applied to the vehicle by the player</summary>
	///<param name='SetThrottleInput'>Value of the throttle applied</param>  
	void SetThrottleInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Sets the steering direction and magnitude of it to the vehicle</summary>
	///<param name='SetSteeringInput'>Value of the steering applied, positive and negative give steering direction</param>  
	void SetSteeringInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Sets the current braking applied to the vehicle by the player</summary>
	///<param name='SetBrakeInput'>Value of the brakes applied</param>  
	void SetBrakeInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Gets the current speed of the vehicle</summary>
	///<returns>Current vehicle speed</returns>  
	float GetVehicleForwardSpeed() const;

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Gets the third person view camera for the vehicle</summary>
	///<returns>Current vehicle speed</returns>  
	UCameraComponent* GetChaseCamera();

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Gets first person view camera for the vehicle</summary>
	///<returns>Current vehicle speed</returns>  
	UCameraComponent* GetInternalCamera();

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ChaseCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* InternalCamera;
};
