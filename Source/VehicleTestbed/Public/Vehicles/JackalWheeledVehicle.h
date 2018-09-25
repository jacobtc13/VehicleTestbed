// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/TestbedWheeledVehicle.h"
#include "JackalWheeledVehicle.generated.h"

UCLASS()
///<summary>Class to represent the Clearpath Jackal.</summary>
class VEHICLETESTBED_API AJackalWheeledVehicle : public ATestbedWheeledVehicle
{
	GENERATED_BODY()

public:
	AJackalWheeledVehicle();

	~AJackalWheeledVehicle();
};
