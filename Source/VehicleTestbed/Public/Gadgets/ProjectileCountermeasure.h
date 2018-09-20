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

	wchar_t* MeshLocation = TEXT("SkeletalMesh'/Game/Vehicle/Countermeasures/JackalProjectileCM.JackalProjectileCM'");

	wchar_t* PhysicsAssetLocation = TEXT("PhysicsAsset'/Game/Vehicle/Countermeasures/JackalProjectileCM_PhysicsAsset.JackalProjectileCM_PhysicsAsset'");
	
	virtual void InitialiseMesh() override;
};
