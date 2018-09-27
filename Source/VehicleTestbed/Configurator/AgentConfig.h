#pragma once

#include "Configurator/RapidXML/rapidxml.hpp"
#include "Configurator/ConfigBase.h"

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UAgentConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	UAgentConfig();
	~UAgentConfig();

	virtual rapidxml::xml_node<>* GetXMLNode() override;

protected:
	UClass * AgentClass;
};

