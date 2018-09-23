// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadgets/Gadget.h"
#include "ShieldCountermeasure.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API AShieldCountermeasure : public AGadget
{
	GENERATED_BODY()
	
public:
	AShieldCountermeasure();

	~AShieldCountermeasure();

protected:
	bool bHasMesh = true;

	wchar_t* MeshLocation = TEXT("StaticMesh'/Game/Vehicle/Countermeasures/JackalShield.JackalShield'");

	wchar_t* PhysicsAssetLocation = TEXT("PhysicsAsset'/Game/Vehicle/Jackal/Jackal_PhysicsAsset.Jackal_PhysicsAsset'");

	virtual void InitialiseMesh() override;
};
