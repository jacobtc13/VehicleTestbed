// Fill out your copyright notice in the Description page of Project Settings.

#include "ScenarioConfig.h"
#include "Configurator.h"

rapidxml::xml_node<>* UScenarioConfig::GetXMLNode()
{
	using namespace rapidxml;
	xml_document<> Doc;
	xml_node<>* BaseNode = Doc.allocate_node(node_element, "Scenario");
	TArray<FString> AgentFiles;
	Agents.GetKeys(AgentFiles);
	for (FString Agent : AgentFiles)
	{
		xml_node<>* AgentNode = Doc.allocate_node(node_element, "Agent", TCHAR_TO_UTF8(*Agent));
		BaseNode->append_node(AgentNode);
	}
	xml_node<>* MapNode = Doc.allocate_node(node_element, "Map", TCHAR_TO_UTF8(*MapName.ToString()));
	BaseNode->append_node(MapNode);

	return BaseNode;
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
			if (UAgentConfig* NewAgent = dynamic_cast<UAgentConfig*>(UConfigurator::LoadConfig(TCHAR_TO_UTF8(*Pair.Key))))
			{
				// New Agent is valid
				Pair.Value = NewAgent;
				// TODO: Register the new agent config with whatever static thing that keeps track of all the configs
			}
			else
			{
				// Not valid
				// TODO: Error handling when one of the files couldn't be loaded
			}
		}
		AgentsArray.Add(Pair.Value);
	}
	return AgentsArray;
}

void UScenarioConfig::AddAgent(const FString& FileLocation, UAgentConfig* AgentConfig/*= nullptr*/)
{
	Agents.Add(FileLocation, AgentConfig);
}

void UScenarioConfig::RemoveAgentByFile(const FString& FileLocation)
{
	Agents.Remove(FileLocation);
}

void UScenarioConfig::RemoveAgentByObject(const UAgentConfig* AgentConfig)
{
	Agents.Remove(AgentConfig->GetFileLocation());
}

FName UScenarioConfig::GetMapName() const
{
	return MapName;
}

void UScenarioConfig::SetMapName(FName NewMapName)
{
	MapName = NewMapName;
}
