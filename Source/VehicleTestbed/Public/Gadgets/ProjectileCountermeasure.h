// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadgets/Gadget.h"
#include "ProjectileCountermeasure.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API AProjectileCountermeasure : public AGadget
{
	GENERATED_BODY()
	
public:
	AProjectileCountermeasure();

	~AProjectileCountermeasure();

	void AttachComponent(ATestbedWheeledVehicle* Vehicle, FName SocketName);

	///<summary>Activates the countermeasure based on desired behaviour</summary>
	virtual void Activate();

protected:
	bool bHasMesh = true;

	wchar_t* SkeletalMeshLocation = TEXT("SkeletalMesh'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'");

	wchar_t* PhysicsAssetLocation = TEXT("PhysicsAsset'/Game/Vehicle/Jackal/Jackal_PhysicsAsset.Jackal_PhysicsAsset'");
	
	
};
