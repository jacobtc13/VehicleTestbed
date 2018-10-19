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
	///<summary>Generates a rapidxml node structure from the information in this object</summary>
	///<returns>A pointer to a rapidxml node structure depicting the information from this object</returns>
	rapidxml::xml_node<>* GetXMLNode() override;

	UFUNCTION()
	///<summary>Returns an array of the file locations of the agent configs used in this scenario</summary>
	///<returns>An array of file locations of the agents configs used in this scenario</returns>
	TArray<FString> GetAgentFileLocations() const;

	UFUNCTION()
	///<summary>Returns an array of Agent Config objects used by this scenario, creating them from file if they don't exist in memory</summary>
	///<returns>An array of Agent Config objects used by this scenario</returns>
	TArray<UAgentConfig*> GetAgents();

	UFUNCTION()
	///<summary>Adds an agent to the scenario
	///<param="FileLocation">The string representation of the file location used for this Agent Config</param>
	///<param="AgentConfig">An optional Agent Config object if it is already loaded in memory</param>
	void AddAgent(const FString& FileLocation, UAgentConfig* AgentConfig = nullptr);

	UFUNCTION()
	///<summary>Removes the selected agent config from this scenario</summary>
	///<param="FileLocation">The string representation of the file location of the Agent Config to remove</param>
	void RemoveAgentByFile(const FString& FileLocation);

	UFUNCTION()
	///<summary>Removes the selected agent config from this scenario</summary>
	///<param="AgentConfig">The config object of the agent to remove.  Uses the FileLocation of the config object.</param>
	void RemoveAgentByObject(const UAgentConfig* AgentConfig);

	UFUNCTION()
	///<summary>Returns the name of the map used in this scenario</summmary>
	///<returns>The name of the map uesd in this scenario</returns>
	FName GetMapName() const;

	UFUNCTION()
	///<summary>Sets the name of the map used for this scenario</summary>
	///<param="NewMapName">The name of the new map used for this scenario</param>
	void SetMapName(FName NewMapName);

private:
	UPROPERTY()
	TMap<FString, UAgentConfig*> Agents;
	UPROPERTY()
	FName MapName;

	//TODO: Spawn points
};
