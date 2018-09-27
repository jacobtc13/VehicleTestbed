#pragma once

#include "Configurator/RapidXML/rapidxml.hpp"

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

	static void LoadAgentConfig(FString file);

	static void SaveAgentConfig(FString file, UClass* agent);
};

