// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalWheeledVehicle.h"

AJackalWheeledVehicle::AJackalWheeledVehicle()
{
	// Setup Jackal specific camera distances
	ChaseCamera->RelativeLocation = FVector(-315.0f, 2.0f, 104.0f);
	CameraSpringArm->RelativeRotation = FRotator(-15.f, 0.f, 0.f);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	InternalCamera->RelativeLocation = FVector(41.0, 0.0f, 65.0f);

	OverheadCamera->RelativeLocation = FVector(0.f, 0.f, 1000.f);
	OverheadCamera->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
}

AJackalWheeledVehicle::~AJackalWheeledVehicle()
{
}


