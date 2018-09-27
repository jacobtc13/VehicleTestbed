#pragma once

#include "Configurator/RapidXML/rapidxml.hpp"

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UAgentConfig : public UObject
{
	GENERATED_BODY()

public:
	UAgentConfig();
	~UAgentConfig();

	virtual rapidxml::xml_node<>* GetXMLNode();

protected:
	UClass * AgentClass;
};

