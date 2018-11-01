#pragma once

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <string>

#include "AgentConfig.h"
#include "ScenarioConfig.h"
#include "ConfigBase.h"

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
	UFUNCTION(BlueprintCallable, meta = (WorldContext = ContextObject))
	///<summary>Runs the saved scenario, setting things up and spawning things into the current map</summary>
	///<param name="ContextObject">The context object used to load the map, the widget calling this function will suffice</param>
	static void StartScenario(UObject* ContextObject);

	static UConfigBase* LoadConfig(std::string Filename);

	static void SaveConfig(std::string Filename, UConfigBase* Config);

	static void ReloadConfig(UConfigBase* Config);

	UFUNCTION(BlueprintGetter)
	static FString GetScenario();

	UFUNCTION(BlueprintSetter)
	static void SetScenario(FString ScenarioFile);

private:
	static FString Scenario;
};
