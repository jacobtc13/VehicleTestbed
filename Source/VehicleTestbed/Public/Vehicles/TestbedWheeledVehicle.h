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
	///<param name='Value'>Value of the throttle applied</param>  
	void SetThrottleInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Sets the steering direction and magnitude of it to the vehicle</summary>
	///<param name='Value'>Value of the steering applied, positive and negative give steering direction</param>  
	void SetSteeringInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Sets the current braking applied to the vehicle by the player</summary>
	///<param name='Value'>Value of the brakes applied</param>  
	void SetBrakeInput(float Value);

	UFUNCTION(Category = "Testbed Wheeled Vehicle", BlueprintCallable)
	///<summary>Gets the current speed of the vehicle</summary>
	///<returns>Current vehicle speed</returns>  
	float GetVehicleForwardSpeed() const;

	UFUNCTION()
	///<summary>Gets first person view camera for the vehicle</summary>
	void SwitchToOverheadCamera();

	UFUNCTION()
	///<summary>Gets first person view camera for the vehicle</summary>
	void SwitchToInternalCamera();

	UFUNCTION()
	///<summary>Gets first person view camera for the vehicle</summary>
	void SwitchToChaseCamera();

	UFUNCTION()
	///<summary>Returns true if the actor can be possessed in game</summary>
	bool IsPossessable() { return bIsPosessable; };

private:
	UFUNCTION()
	///<summary>Activates the selected camera and deactivates the previously active camera</summary>
	///<param name='NewActiveCamera'>The next camera which will be set as the active camera</param>  
	void SwitchActiveCamera(UCameraComponent* NewActiveCamera);

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ChaseCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* InternalCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* OverheadCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ActiveCamera;
	UPROPERTY(EditAnywhere)
	bool bIsPosessable = true;
};
