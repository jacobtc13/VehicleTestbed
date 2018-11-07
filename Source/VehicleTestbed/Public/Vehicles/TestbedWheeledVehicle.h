#pragma once

#include "WheeledVehicle.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GadgetMountingNode.h"
#include "MountablePawn.h"
#include "Engine/SkeletalMeshSocket.h"
#include "TestbedWheeledVehicle.generated.h"

UCLASS(Abstract)
///<summary>Base class for all wheeled vehicle actors. Sets up cameras and controls for player usage.</summary>
class VEHICLETESTBED_API ATestbedWheeledVehicle : public AWheeledVehicle, public IMountablePawn
{
	GENERATED_BODY()

public:
	///<summary>Default Constructor</summary>
	ATestbedWheeledVehicle();
	
	///<summary>Default Deconstructor</summary>
	~ATestbedWheeledVehicle();

	///<summary>Allow actors to initialize themselves on the C++ side</summary>
	void PostInitializeComponents();

	UFUNCTION()
	///<summary>Sets the current throttle applied to the vehicle by the player</summary>
	///<param name='Value'>Value of the throttle applied</param>  
	void SetThrottleInput(float Value);

	UFUNCTION()
	///<summary>Sets the steering direction and magnitude of it to the vehicle</summary>
	///<param name='Value'>Value of the steering applied, positive and negative give steering direction</param>  
	void SetSteeringInput(float Value);

	UFUNCTION()
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

	UFUNCTION()
	///<summary>Get a TArray of pointers to the UGadgetMouningNodes on the vehicle</summary>
	///<returns>A TArray of pointers to the UGadgetMountingNodes</returns>
	virtual TArray<UGadgetMountingNode*> GetMountingNodes() override;

	UFUNCTION()
	///<summary>Search for and returns a GadgetMountingNode that is associated with a socket name. Can return a nullptr if nothing is found</summary>
	///<params name = 'SocketName'>The socket name that is associated with the GadgetMountingNode being searched for</params>
	///<returns>The GadgetMountingNode that is associated with the SocketName</returns>
	virtual UGadgetMountingNode* GetMountingNodeBySocketName(FName SocketName) override;

	UFUNCTION()
	///<summary> GadgetMountingNodes related to the socket denoted by FName toAddTo</summary>
	///<params name = 'GadgetClass'>A static class of the gadget that will be attached to the pawn</params>
	///<params name = 'Socket'>The socket on the skeletal mesh of the pawn</params>
	virtual void MountGadget(TSubclassOf<AGadget> GadgetClass, USkeletalMeshSocket* Socket) override;


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

	UPROPERTY(EditAnywhere, Category = "Gadget")
	TArray<UGadgetMountingNode*> GadgetMountingNodes;
};
