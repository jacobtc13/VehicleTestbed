#include "ScenarioConfig.h"
#include "Configurator.h"
#include "MessageDialog.h"
#include "GameFramework/GameModeBase.h"
#include "DataRecorder.h"
#include "EventRecorder/EventRecorder.h"

rapidxml::xml_node<>* UScenarioConfig::GetXMLNode()
{
	using namespace rapidxml;
	xml_document<> Doc;

	// Save the config as a "Scenario" type
	xml_node<>* BaseNode = Doc.allocate_node(node_element, "Scenario");

	// Save the map name
	xml_node<>* MapNode = Doc.allocate_node(node_element, "Map", TCHAR_TO_UTF8(*MapName.ToString()));
	BaseNode->append_node(MapNode);

	// Save the agents used
	TArray<FString> AgentFiles;
	Agents.GetKeys(AgentFiles);
	for (const FString& Agent : AgentFiles)
	{
		xml_node<>* AgentNode = Doc.allocate_node(node_element, "Agent", TCHAR_TO_UTF8(*Agent));
		BaseNode->append_node(AgentNode);
	}

	// Save the spawn points and which agents go with them
	for (const auto& Pair : SpawnPoints)
	{
		xml_node<>* SpawnNode = Doc.allocate_node(node_element, "Spawn");
		xml_node<>* SpawnNameNode = Doc.allocate_node(node_element, "Name", TCHAR_TO_UTF8(*Pair.Key.ToString()));
		SpawnNode->append_node(SpawnNameNode);
		xml_node<>* SpawnAgentNode = Doc.allocate_node(node_element, "Agent", TCHAR_TO_UTF8(*Pair.Value));
		SpawnNode->append_node(SpawnAgentNode);
		BaseNode->append_node(SpawnNode);
	}

	// Save the data recording output file
	xml_node<>* DataRecordingNode = Doc.allocate_node(node_element, "DataRecordingOutput", TCHAR_TO_UTF8(*DataRecordOutputFolder));
	BaseNode->append_node(DataRecordingNode);

	// Save the event recording output file
	xml_node<>* EventRecordingNode = Doc.allocate_node(node_element, "EventRecordingOutput", TCHAR_TO_UTF8(*EventRecordOutputFolder));
	BaseNode->append_node(EventRecordingNode);

	// Add CommsConfig

	return BaseNode;
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
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "Map"))
	{
		MapName = Node->value();
	}
	else
	{
		return false;
	}

	// Find agents
	// this is the recommended way to loop through rapidxml
	// Stops when it gets to a non-Agent node
	for (Node = Node->next_sibling(); Node && ((std::string)Node->name() == "Agent"); Node = Node->next_sibling())
	{
		Agents.Add(Node->value());
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
		SpawnPoints.Add(NameNode->value(), AgentNode->value());
	}

	// Get data recording output folder
	if (Node && ((std::string)Node->name() == "DataRecordingOutput"))
	{
		DataRecordOutputFolder = Node->value();
	}
	else
	{
		return false;
	}

	// Get event recording output folder
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "EventRecordingOutput"))
	{
		EventRecordOutputFolder = Node->value();
	}
	else
	{
		return false;
	}

	// Add CommsConfig

	return true;
}

bool UScenarioConfig::Instantiate(UObject* ContextObject)
{
	if (!ContextObject || !ContextObject->ImplementsGetWorld())
	{
		return false;
	}
	// Set the data recorder output location
	if (UDataRecorder* DataRecorder = Cast<UDataRecorder>(UGameplayStatics::GetGameMode(ContextObject)->GetDefaultSubobjectByName(TEXT("Data Recorder"))))
	{
		DataRecorder->SetFilePath(TCHAR_TO_UTF8(*DataRecordOutputFolder));
	}
	else
	{
		return false;
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

	// TODO: Tie in with agent spawn controller

	// TODO: Add CommsConfig

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

bool LoadAgentFromFile(TPair<FString, UAgentConfig*>& Pair)
{
	if (UAgentConfig* NewAgent = Cast<UAgentConfig>(UConfigurator::LoadConfig(TCHAR_TO_UTF8(*Pair.Key))))
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
	if (AgentFile == "")
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
