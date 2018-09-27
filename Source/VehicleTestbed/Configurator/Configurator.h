#pragma once

#include "Configurator/RapidXML/rapidxml.hpp"
#include "Configurator/RapidXML/rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <string>

#include "Configurator/AgentConfig.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Configurator.generated.h"

// Abstract tag blocks instantiation of this class.
UCLASS(Abstract)
///<summary>Static function library to read and write configurations</summary>
class UConfigurator : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:
	static UConfigBase* LoadConfig(std::string Filename);

	static void SaveConfig(std::string Filename, UAgentConfig* AgentConfig);
};

