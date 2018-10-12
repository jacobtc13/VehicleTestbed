#pragma once

#include "ConfigBase.h"
#include "AgentConfig.h"

#include "CoreMinimal.h"
#include "ScenarioConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UScenarioConfig : public UConfigBase
{
	GENERATED_BODY()
	
public:
	///<summary>Default Constructor</summary>
	UScenarioConfig() = default;
	///<summary>Destructor</summary>
	~UScenarioConfig() = default;
	
	///<summary>Generates a rapidxml node structure from the information in this object</summary>
	///<returns>A pointer to a rapidxml node structure depicting the information from this object</returns>
	rapidxml::xml_node<>* GetXMLNode() override;

private:
	TLinkedList<UAgentConfig*> Agents;
	// TODO: Spawn points
	FName MapName;
};
