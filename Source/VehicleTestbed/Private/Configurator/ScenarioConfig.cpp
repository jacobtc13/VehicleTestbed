// Fill out your copyright notice in the Description page of Project Settings.

#include "ScenarioConfig.h"

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
