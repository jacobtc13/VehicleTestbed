// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestbedWheeledVehicle.h"
#include "Gadget.generated.h"

/**
 * Base class for mounting/dismounting to an AMountablePAwn
 */
UCLASS()
class VEHICLETESTBED_API AGadget : public AActor
{
	GENERATED_BODY()

public:
	AGadget();

	~AGadget();

	void AttachComponent(ATestbedWheeledVehicle* Vehicle, FName SocketName);

	///<summary>Activates the countermeasure based on desired behaviour</summary>
	virtual void Activate();
};
