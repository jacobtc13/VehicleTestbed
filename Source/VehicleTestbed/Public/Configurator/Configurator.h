#pragma once

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <string>

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

	UFUNCTION()
	///<summary>Loads a config object from the specified file</summary>
	///<param name="Filename">The full path of the file to load from</param>
	///<returns>The config object which was loaded, or nullptr if it wasn't</returns>
	static UConfigBase* LoadConfig(FString Filename);

	UFUNCTION()
	///<summary>Saves the config object at the specified file location</summary>
	///<param name="Config">The config object to save</param>
	static void SaveConfig(UConfigBase* Config);

	UFUNCTION(BlueprintCallable)
	///<summary>Reloads a config object from the file it is based on</summary>
	///<param name="Config">The config object to reload</param>
	static void ReloadConfig(UConfigBase* Config);

	UFUNCTION(BlueprintGetter)
	static FString GetScenario();

	UFUNCTION(BlueprintSetter)
	static void SetScenario(FString ScenarioFile);

private:
	static FString Scenario;
};
