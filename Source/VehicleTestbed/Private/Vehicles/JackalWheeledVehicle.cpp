// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalWheeledVehicle.h"

AJackalWheeledVehicle::AJackalWheeledVehicle()
{
	// Setup Jackal specific camera distances
	ChaseCamera->RelativeLocation = FVector(-300.0f, 15.0f, 50.0f);

	InternalCamera->RelativeLocation = FVector(41.0, 0.0f, 65.0f);
}

AJackalWheeledVehicle::~AJackalWheeledVehicle()
{
}


