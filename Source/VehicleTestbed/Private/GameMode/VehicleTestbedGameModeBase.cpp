// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleTestbedGameModeBase.h"
#include "Configurator.h"
#include "EventRecorder.h"

AVehicleTestbedGameModeBase::AVehicleTestbedGameModeBase()
{
	dataRecorder = CreateDefaultSubobject<UDataRecorder>(TEXT("Data Recorder"));
}

void AVehicleTestbedGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	// Add collectors to data recorder
	// TODO: Rewrite this to load from file/menu and do bindings dynamically
	DataCollector<int32>* myCollector = new DataCollector<int32>();
	myCollector->FGetDelegate.BindUObject(this, &AVehicleTestbedGameModeBase::GetNumPlayers);
	dataRecorder->AddCollector(myCollector);
}

void AVehicleTestbedGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	dataRecorder->Start();
	UEventRecorder::Start();
}

void AVehicleTestbedGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	dataRecorder->Stop();
	UEventRecorder::Stop();
	Super::EndPlay(EndPlayReason);
}

UDataRecorder* AVehicleTestbedGameModeBase::GetDataRecorder() const
{
	return dataRecorder;
}
