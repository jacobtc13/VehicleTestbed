// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/TestbedWheeledVehicle.h"
#include "Gadget.h"
#include "GadgetMountingNode.h"
#include "JackalWheeledVehicle.generated.h"

UCLASS(Abstract)
///<summary>Class to represent the Clearpath Jackal.</summary>
class VEHICLETESTBED_API AJackalWheeledVehicle : public ATestbedWheeledVehicle
{
	GENERATED_BODY()

public:
	///<summary>Default Constructor</summary>
	AJackalWheeledVehicle();

	///<summary>Default Deconstructor</summary>
	~AJackalWheeledVehicle();

	///<summary>Allow actors to initialize themselves on the C++ side</summary>
	void PostInitializeComponents();
};
