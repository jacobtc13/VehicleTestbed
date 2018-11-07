#include "ScenarioConfig.h"
#include "Configurator.h"
#include "MessageDialog.h"
#include "VehicleTestbedGameModeBase.h"
#include "DataRecorder.h"
#include "EventRecorder.h"
#include "CommConfig.h"
#include "SpawnController.h"

UScenarioConfig::UScenarioConfig()
{
	CommConfig.Object = nullptr;
}

bool LoadAgentFromFile(TPair<FString, UAgentConfig*>& Pair)
{
	if (UAgentConfig* NewAgent = Cast<UAgentConfig>(UConfigurator::LoadConfig(Pair.Key)))
	{
		// New Agent is valid
		Pair.Value = NewAgent;
		// TODO: Register the new agent config with whatever static thing that keeps track of all the configs
		return true;
	}
	else
	{
		// Not valid
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("An agent was not loaded from file correctly. Agent: ") + Pair.Key));
		return false;
	}
}

void UScenarioConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;

	// Save the config as a "Scenario" type
	xml_node<>* BaseNode = OutDocument.allocate_node(node_element, "Scenario");
	OutDocument.append_node(BaseNode);

	// Save the map name
	xml_node<>* MapNode = OutDocument.allocate_node(node_element, "Map", OutDocument.allocate_string(TCHAR_TO_UTF8(*MapName.ToString())));
	BaseNode->append_node(MapNode);

	// Save the agents used
	TArray<FString> AgentFiles;
	Agents.GetKeys(AgentFiles);
	for (const FString& Agent : AgentFiles)
	{
		xml_node<>* AgentNode = OutDocument.allocate_node(node_element, "Agent", OutDocument.allocate_string(TCHAR_TO_UTF8(*Agent)));
		BaseNode->append_node(AgentNode);
	}

	// Save the spawn points and which agents go with them
	for (const auto& Pair : SpawnPoints)
	{
		xml_node<>* SpawnNode = OutDocument.allocate_node(node_element, "Spawn");
		xml_node<>* SpawnNameNode = OutDocument.allocate_node(node_element, "Name", OutDocument.allocate_string(TCHAR_TO_UTF8(*Pair.Key.ToString())));
		SpawnNode->append_node(SpawnNameNode);
		xml_node<>* SpawnAgentNode = OutDocument.allocate_node(node_element, "Agent", OutDocument.allocate_string(TCHAR_TO_UTF8(*Pair.Value)));
		SpawnNode->append_node(SpawnAgentNode);
		BaseNode->append_node(SpawnNode);
	}

	// Save the data recording output file
	xml_node<>* DataRecordingNode = OutDocument.allocate_node(node_element, "DataRecordingOutput", OutDocument.allocate_string(TCHAR_TO_UTF8(*DataRecordOutputFolder)));
	BaseNode->append_node(DataRecordingNode);

	// Save the event recording output file
	xml_node<>* EventRecordingNode = OutDocument.allocate_node(node_element, "EventRecordingOutput", OutDocument.allocate_string(TCHAR_TO_UTF8(*EventRecordOutputFolder)));
	BaseNode->append_node(EventRecordingNode);

	// Save the communications config file
	xml_node<>* CommNode = OutDocument.allocate_node(node_element, "Communication", OutDocument.allocate_string(TCHAR_TO_UTF8(*GetCommConfig())));
	BaseNode->append_node(CommNode);
}

bool UScenarioConfig::InitializeFromXML(rapidxml::xml_document<>& Doc)
{
	using namespace rapidxml;
	xml_node<>* Node = Doc.first_node();

	// Check is a scenario
	if (Node && ((std::string)Node->name() != "Scenario"))
	{
		return false;
	}

	// Check for a map next
	Node = Node->first_node();
	if (Node && ((std::string)Node->name() == "Map"))
	{
		SetMapName(Node->value());
	}
	else return false;

	// Find agents
	// this is the recommended way to loop through rapidxml
	// Stops when it gets to a non-Agent node
	for (Node = Node->next_sibling(); Node && ((std::string)Node->name() == "Agent"); Node = Node->next_sibling())
	{
		AddAgent(Node->value());
	}

	// Find spawns
	for (; Node && (std::string)Node->name() == "Spawn"; Node = Node->next_sibling())
	{
		xml_node<>* NameNode = Node->first_node("Name");
		xml_node<>* AgentNode = Node->first_node("Agent");
		if (!NameNode || !AgentNode)
		{
			// Bad file structure error
			return false;
		}
		AddSpawn(NameNode->value(), AgentNode->value());
	}

	// Get data recording output folder
	if (Node && ((std::string)Node->name() == "DataRecordingOutput"))
	{
		SetDataRecordingOutputFolder(Node->value());
	}
	else return false;

	// Get event recording output folder
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "EventRecordingOutput"))
	{
		SetEventRecordingOuptutFolder(Node->value());
	}
	else return false;

	// Get the Communications config
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "Communication"))
	{
		SetCommConfig(Node->value());
	}
	else return false;

	return true;
}

bool UScenarioConfig::Instantiate(UObject* ContextObject)
{
	if (!ContextObject || !ContextObject->ImplementsGetWorld())
	{
		return false;
	}

	// Check that we're on the right map
	if (UGameplayStatics::GetCurrentLevelName(ContextObject) != GetMapName().ToString())
	{
		// Not on the expected map
		return false;
	}

	// Set the data recorder output location
	if (AVehicleTestbedGameModeBase* GameMode = Cast<AVehicleTestbedGameModeBase>(UGameplayStatics::GetGameMode(ContextObject)))
	{
		if (UDataRecorder* DataRecorder = GameMode->GetDataRecorder())
		{
			DataRecorder->SetFilePath(TCHAR_TO_UTF8(*DataRecordOutputFolder));
		}
		else
		{
			// Data recorder is null
		}
	}

	// Set the event recorder output location
	UEventRecorder::SetFolderOutput(EventRecordOutputFolder);

	// Load agents
	for (auto& Agent : Agents)
	{
		if (!LoadAgentFromFile(Agent))
		{
			return false;
		}
	}

	// Set the comms framework
	if (UCommConfig* CommConfigObject = GetCommConfigObject())
	{
		CommConfigObject->Instantiate(ContextObject);
	}
	else return false;

	// Spawn agents
	SpawnPointList SpawnList;
	for (const auto& SpawnPair : SpawnPoints)
	{
		for (const FName& SpawnName : SpawnList.GetSpawnPointRefs())
		{
			if (SpawnPair.Key == SpawnName)
			{
				// spawn the agent
				if (UAgentConfig* AgentConfig = GetAgent(SpawnPair.Value))
				{
					AgentConfig->Instantiate(ContextObject);

					UClass* AgentClass = AgentConfig->GetAgent()->GetClass();
					FVector AgentLocation = SpawnList.GetSpawnPointbyName(SpawnName).GetLocation();
					FRotator AgentRotation = SpawnList.GetSpawnPointbyName(SpawnName).GetRotation();

					FActorSpawnParameters SpawnParameters;
					SpawnParameters.Name = AgentConfig->GetAgentName();
					SpawnParameters.Template = AgentConfig->GetAgent();

					ATestbedWheeledVehicle* SpawnedAgent = ContextObject->GetWorld()->SpawnActor<ATestbedWheeledVehicle>(AgentClass, AgentLocation, AgentRotation, SpawnParameters);
					if (AgentConfig->GetPossessAtStart())
					{
						UGameplayStatics::GetPlayerController(ContextObject, 0)->Possess(SpawnedAgent);
					}
				}
				else return false;
				break;
			}
		}
	}

	return true;
}

FName UScenarioConfig::GetMapName() const
{
	return MapName;
}

void UScenarioConfig::SetMapName(FName NewMapName)
{
	MapName = NewMapName;
}

TArray<FString> UScenarioConfig::GetAgentFileLocations() const
{
	TArray<FString> AgentFiles;
	Agents.GetKeys(AgentFiles);
	return AgentFiles;
}

TArray<UAgentConfig*> UScenarioConfig::GetAgents()
{
	TArray<UAgentConfig*> AgentsArray;
	for (auto& Pair : Agents)
	{
		if (Pair.Value == nullptr)
		{
			LoadAgentFromFile(Pair);
		}
		AgentsArray.Add(Pair.Value);
	}
	return AgentsArray;
}

UAgentConfig* UScenarioConfig::GetAgent(const FString AgentFile)
{
	for (auto& Pair : Agents)
	{
		if (Pair.Key == AgentFile)
		{
			if (Pair.Value == nullptr)
			{
				LoadAgentFromFile(Pair);
			}
			return Pair.Value;
		}
	}
	return nullptr;
}

void UScenarioConfig::AddAgent(const FString AgentFile, UAgentConfig* AgentConfig/*= nullptr*/)
{
	if (AgentConfig != nullptr)
	{
		if (AgentConfig->GetFileLocation() != AgentFile)
		{
			// AgentConfig does not match the given agent file
			return;
		}
	}
	else
	{
		UConfigBase* Agent = UConfigurator::LoadConfig(AgentFile);
		if (!Agent || !Agent->IsA<UAgentConfig>())
		{
			// Agent is not a valid agent config
			return;
		}
		AgentConfig = Cast<UAgentConfig>(Agent);
	}
	Agents.Add(AgentFile, AgentConfig);
}

void UScenarioConfig::RemoveAgentByFile(const FString AgentFile)
{

	RemoveAllSpawnsOfAgent(AgentFile);
	Agents.Remove(AgentFile);
}

void UScenarioConfig::RemoveAgentByObject(const UAgentConfig* AgentConfig)
{
	if (AgentConfig != nullptr)
	{
		RemoveAgentByFile(AgentConfig->GetFileLocation());
	}
}

TArray<FName> UScenarioConfig::GetSpawnPoints(const FString AgentFile/*=TEXT("")*/) const
{
	TArray<FName> SpawnNames;
	if (AgentFile == "")
	{
		SpawnPoints.GetKeys(SpawnNames);
		return SpawnNames;
	}
	else
	{
		for (const auto& Pair : SpawnPoints)
		{
			if (Pair.Value == AgentFile)
			{
				SpawnNames.Add(Pair.Key);
			}
		}
		return SpawnNames;
	}
}

UAgentConfig* UScenarioConfig::GetAgentBySpawn(const FName SpawnName)
{
	FString* AgentFile = SpawnPoints.Find(SpawnName);
	if (AgentFile != nullptr)
	{
		return GetAgent(*AgentFile);
	}
	return nullptr;
}

bool UScenarioConfig::AddSpawn(const FName SpawnName, const FString AgentFile)
{
	if (AgentFile != "")
	{
		SpawnPoints.Add(SpawnName, AgentFile);
		return true;
	}
	return false;
}

bool UScenarioConfig::ChangeAgentAtSpawn(const FName SpawnName, const FString NewAgentFile)
{
	if (NewAgentFile != "")
	{
		for (auto& Pair : SpawnPoints)
		{
			if (Pair.Key == SpawnName)
			{
				Pair.Value = NewAgentFile;
				return true;
			}
		}
	}
	return false;
}

bool UScenarioConfig::RemoveSpawn(const FName SpawnName)
{
	return SpawnPoints.Remove(SpawnName);
}

int32 UScenarioConfig::RemoveAllSpawnsOfAgent(const FString AgentFile)
{
	int32 NumRemoved = 0;
	TArray<FName> SpawnsToRemove;
	for (const auto& Pair : SpawnPoints)
	{
		if (Pair.Value == AgentFile)
		{
			SpawnsToRemove.Add(Pair.Key);
		}
	}
	for (const FName SpawnName : SpawnsToRemove)
	{
		NumRemoved += SpawnPoints.Remove(SpawnName);
	}
	return NumRemoved;
}

FString UScenarioConfig::GetDataRecordingOutputFolder() const
{
	return DataRecordOutputFolder;
}

void UScenarioConfig::SetDataRecordingOutputFolder(const FString& NewOutputLocation)
{
	DataRecordOutputFolder = NewOutputLocation;
}

FString UScenarioConfig::GetEventRecordingOutputFolder() const
{
	return EventRecordOutputFolder;
}

void UScenarioConfig::SetEventRecordingOuptutFolder(const FString& NewOutputLocation)
{
	EventRecordOutputFolder = NewOutputLocation;
}

FString UScenarioConfig::GetCommConfig() const
{
	return CommConfig.File;
}

UCommConfig* UScenarioConfig::GetCommConfigObject()
{
	if (CommConfig.Object == nullptr)
	{
		SetCommConfig(CommConfig.File);
	}
	return CommConfig.Object;
}

void UScenarioConfig::SetCommConfig(const FString& NewCommConfig)
{
	if (UCommConfig* NewCommConfigObject = Cast<UCommConfig>(UConfigurator::LoadConfig(NewCommConfig)))
	{
		CommConfig.File = NewCommConfig;
		CommConfig.Object = NewCommConfigObject;
	}
}
