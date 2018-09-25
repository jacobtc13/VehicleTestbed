// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadgets/Gadget.h"
#include "ShieldCountermeasure.generated.h"

UCLASS()
///<summary>Gadget that represents a shield countermeasure that can be mounted to a MountablePawn</summary>
class VEHICLETESTBED_API AShieldCountermeasure : public AGadget
{
	GENERATED_BODY()
	
public:
	AShieldCountermeasure();

	~AShieldCountermeasure();

protected:
	wchar_t* MeshLocation = TEXT("StaticMesh'/Game/Vehicle/Countermeasures/JackalShield.JackalShield'");

	wchar_t* PhysicsAssetLocation = TEXT("PhysicsAsset'/Game/Vehicle/Jackal/Jackal_PhysicsAsset.Jackal_PhysicsAsset'");

	///<summary>Initializes the asset to use the appropriate mesh and physics assets</summary>
	virtual void InitialiseMesh() override;
};
