#pragma once

#include "rapidxml.hpp"
#include "ConfigBase.h"
#include "PlayerController/TestbedPlayerController.h"

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UAgentConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	UAgentConfig();
	UAgentConfig(rapidxml::xml_node<>* Node);
	~UAgentConfig();

	virtual rapidxml::xml_node<>* GetXMLNode() override;

protected:
	UClass * AgentClass;
	FString AgentName;
	//Mesh??

	TSubclassOf<ATestbedPlayerController> Controller;

	TMap<FString, FString> Properties;
};
