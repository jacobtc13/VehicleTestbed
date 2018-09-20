// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestbedWheeledVehicle.h"
#include "Gadget.generated.h"

/**
 * Base class for mounting/dismounting to an AMountablePAwn
 */
UCLASS()
class VEHICLETESTBED_API AGadget : public APawn
{
	GENERATED_BODY()

public:
	AGadget();

	~AGadget();

	void AttachComponent(ATestbedWheeledVehicle* Vehicle, FName SocketName);

	///<summary>Activates the countermeasure based on desired behaviour</summary>
	virtual void Activate();

protected:
	bool bHasMesh = false;

	wchar_t* MeshLocation;// = TEXT("SkeletalMesh'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'");

	wchar_t* PhysicsAssetLocation;// = TEXT("PhysicsAsset'/Game/Vehicle/Jackal/Jackal_PhysicsAsset.Jackal_PhysicsAsset'");

	virtual void InitialiseMesh();
};
