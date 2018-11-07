// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleTestbedGameModeBase.h"
#include "Configurator.h"
#include "ScenarioConfig.h"
#include "CommDistributor.h"
#include "ThirtyMetreSNR.h"

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

	UConfigurator::SetScenario(FPaths::ProjectDir() + TEXT("Configurations/Scenarios/DemoScenario.xml"));

	if (UGameplayStatics::GetCurrentLevelName(this) == "Desert")
	{
		// Load the scenario
		UConfigurator::StartScenario(this);
	}
	else
	{
		UAgentConfig* AgentConfig = NewObject<UAgentConfig>();
		AgentConfig->SetFileLocation(FPaths::ProjectDir() + TEXT("Configurations/Agents/DemoAgent.xml"));
		UCommConfig* CommConfig = NewObject<UCommConfig>();
		CommConfig->SetFileLocation(FPaths::ProjectDir() + TEXT("Configurations/Communication/DemoComm.xml"));
		UScenarioConfig* ScenarioConfig = NewObject<UScenarioConfig>();
		ScenarioConfig->SetFileLocation(FPaths::ProjectDir() + TEXT("Configurations/Scenarios/DemoScenario.xml"));

		AgentConfig->AddGadget(TEXT("ShieldCountermeasure"));
		AgentConfig->SetAgentClassName(TEXT("Jackal_BP_C"));
		AgentConfig->SetAgentName("DemoAgent");
		AgentConfig->SetPossessAtStart(true);
		UConfigurator::SaveConfig(AgentConfig);

		CommConfig->SetDefaultModelName(TEXT("ThirtyMetreSNR"));
		UConfigurator::SaveConfig(CommConfig);

		ScenarioConfig->AddAgent(AgentConfig->GetFileLocation(), AgentConfig);
		ScenarioConfig->AddSpawn(TEXT("ALLY1"), AgentConfig->GetFileLocation());
		ScenarioConfig->SetCommConfig(CommConfig->GetFileLocation());
		ScenarioConfig->SetMapName(TEXT("Desert"));
		ScenarioConfig->SetDataRecordingOutputFolder(FPaths::ProjectDir() + TEXT("Logs"));
		ScenarioConfig->SetEventRecordingOuptutFolder(FPaths::ProjectDir() + TEXT("Logs"));
		UConfigurator::SaveConfig(ScenarioConfig);

		UCommDistributor::SetDefaultPropagation(NewObject<UThirtyMetreSNR>());
	}

	dataRecorder->Start();
	UEventRecorder::Start();
}

void AVehicleTestbedGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	dataRecorder->Stop();
	UCommDistributor::EndPlay();
	UEventRecorder::Stop();
	Super::EndPlay(EndPlayReason);
}

UDataRecorder* AVehicleTestbedGameModeBase::GetDataRecorder() const
{
	return dataRecorder;
}
