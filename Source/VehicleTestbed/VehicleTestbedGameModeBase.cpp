// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleTestbedGameModeBase.h"

AVehicleTestbedGameModeBase::AVehicleTestbedGameModeBase()
{
	dataRecorder = CreateDefaultSubobject<UDataRecorder>(TEXT("Data Recorder"));
}

void AVehicleTestbedGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Add collectors to data recorder
	DataCollector<int32> myCollector;
	myCollector.FGetDelegate.BindUObject(this, &AVehicleTestbedGameModeBase::GetNumPlayers);
	dataRecorder->AddCollector(&myCollector);

	dataRecorder->Start();
}

void AVehicleTestbedGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	dataRecorder->Stop();
	Super::EndPlay(EndPlayReason);
}
