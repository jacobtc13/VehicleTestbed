// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleTestbedGameModeBase.h"

AVehicleTestbedGameModeBase::AVehicleTestbedGameModeBase() : dataRecorder() { }

void AVehicleTestbedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	dataRecorder->Start();
}

void AVehicleTestbedGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	dataRecorder->Stop();
	Super::EndPlay(EndPlayReason);
}
