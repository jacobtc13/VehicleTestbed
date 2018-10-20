#include "ScenarioConfig.h"
#include "Configurator.h"

rapidxml::xml_node<>* UScenarioConfig::GetXMLNode()
{
	using namespace rapidxml;
	xml_document<> Doc;
	xml_node<>* BaseNode = Doc.allocate_node(node_element, "Scenario");
	xml_node<>* MapNode = Doc.allocate_node(node_element, "Map", TCHAR_TO_UTF8(*MapName.ToString()));
	BaseNode->append_node(MapNode);
	TArray<FString> AgentFiles;
	Agents.GetKeys(AgentFiles);
	for (FString Agent : AgentFiles)
	{
		xml_node<>* AgentNode = Doc.allocate_node(node_element, "Agent", TCHAR_TO_UTF8(*Agent));
		BaseNode->append_node(AgentNode);
	}

	return BaseNode;
}

bool UScenarioConfig::InitializeFromXML(rapidxml::xml_document<>& Doc)
{
	using namespace rapidxml;
	xml_node<>* Node = Doc.first_node();
	// Check is a scenario
	if ((std::string)Node->name() != "Scenario")
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
	// this is the recommended way to loop through rapidxml
	// Stops when it gets to a non-Agent node
	for (Node = Node->next_sibling(); Node && ((std::string)Node->name() == "Agent"); Node = Node->next_sibling())
	{
		Agents.Add(Node->value());
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

bool LoadAgentForMap(TPair<FString, UAgentConfig*>& Pair)
{
	if (UAgentConfig* NewAgent = dynamic_cast<UAgentConfig*>(UConfigurator::LoadConfig(TCHAR_TO_UTF8(*Pair.Key))))
	{
		// New Agent is valid
		Pair.Value = NewAgent;
		// TODO: Register the new agent config with whatever static thing that keeps track of all the configs
		return true;
	}
	else
	{
		// Not valid
		// TODO: Error handling when one of the files couldn't be loaded / what was loaded wasn't an Agent Config
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
			LoadAgentForMap(Pair);
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
				LoadAgentForMap(Pair);
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

TArray<FName> UScenarioConfig::GetSpawnPoints(const UAgentConfig* AgentConfig/*=nullptr*/) const
{
	TArray<FName> SpawnNames;
	if (AgentConfig == nullptr)
	{
		SpawnPoints.GetKeys(SpawnNames);
		return SpawnNames;
	}
	else
	{
		for (const auto& Pair : SpawnPoints)
		{
			if (Pair.Value == AgentConfig->GetFileLocation())
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

bool UScenarioConfig::AddSpawn(const FName SpawnName, const UAgentConfig* AgentConfig)
{
	if (AgentConfig != nullptr)
	{
		SpawnPoints.Add(SpawnName, AgentConfig->GetFileLocation());
		return true;
	}
	return false;
}

bool UScenarioConfig::ChangeAgentAtSpawn(const FName SpawnName, const UAgentConfig* NewAgentConfig)
{
	if (NewAgentConfig != nullptr)
	{
		for (auto& Pair : SpawnPoints)
		{
			if (Pair.Key == SpawnName)
			{
				Pair.Value = NewAgentConfig->GetFileLocation();
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
	for (FName SpawnName : SpawnsToRemove)
	{
		NumRemoved += SpawnPoints.Remove(SpawnName);
	}
	return NumRemoved;
}
