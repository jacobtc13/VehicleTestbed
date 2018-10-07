// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadgets/Gadget.h"
#include "ProjectileCountermeasure.generated.h"

UCLASS()
///<summary>Gadget that represents a projectile firing countermeasure that can be mounted to a MountablePawn</summary>
class VEHICLETESTBED_API AProjectileCountermeasure : public AGadget
{
	GENERATED_BODY()
	
public:
	///<summary>Default Constructor</summary>
	AProjectileCountermeasure();

	///<summary>Default Deconstructor</summary>
	~AProjectileCountermeasure();

	///<summary>Activates the countermeasure based on desired behaviour</summary>
	virtual void Activate();

protected:
	wchar_t* MeshLocation = TEXT("SkeletalMesh'/Game/Vehicle/Countermeasures/JackalProjectileCM.JackalProjectileCM'");

	wchar_t* PhysicsAssetLocation = TEXT("PhysicsAsset'/Game/Vehicle/Countermeasures/JackalProjectileCM_PhysicsAsset.JackalProjectileCM_PhysicsAsset'");
	
	///<summary>Initializes the asset to use the appropriate mesh and physics assets</summary>
	virtual void InitialiseMesh() override;
};
