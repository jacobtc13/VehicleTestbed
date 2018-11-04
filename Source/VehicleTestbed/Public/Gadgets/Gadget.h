// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.generated.h"

/**
 * Base class for mounting/dismounting to an AMountablePAwn
 */
UCLASS()
class VEHICLETESTBED_API AGadget : public APawn
{
	GENERATED_BODY()

public:
	///<summary>Default Constructor</summary>
	AGadget();

	///<summary>Default Deconstructor</summary>
	~AGadget();

	///<summary>Activates the countermeasure based on desired behaviour</summary>
	virtual void Activate();

protected:
	wchar_t* MeshLocation;

	wchar_t* PhysicsAssetLocation;

	///<summary>Initializes the asset to use the appropriate mesh and physics assets</summary>
	virtual void InitialiseMesh();
};
