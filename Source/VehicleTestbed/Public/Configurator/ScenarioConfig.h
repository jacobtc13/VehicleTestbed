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

	///<summary>Initializes this config object from a rapidxml document</summary>
	///<param="doc">The rapidxml document to parse</summary>
	bool InitializeFromXML(rapidxml::xml_document<>& doc) override;

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the name of the map used in this scenario</summmary>
	///<returns>The name of the map uesd in this scenario</returns>
	FName GetMapName() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the name of the map used for this scenario</summary>
	///<param="NewMapName">The name of the new map used for this scenario</param>
	void SetMapName(FName NewMapName);

	UFUNCTION(BlueprintPure)
	///<summary>Returns an array of the file locations of the agent configs used in this scenario</summary>
	///<returns>An array of file locations of the agents configs used in this scenario</returns>
	TArray<FString> GetAgentFileLocations() const;

	UFUNCTION(BlueprintCallable)
	///<summary>Returns an array of Agent Config objects used by this scenario, creating them from file if they don't exist in memory</summary>
	///<returns>An array of Agent Config objects used by this scenario</returns>
	TArray<UAgentConfig*> GetAgents();

	UFUNCTION(BlueprintCallable)
	///<summary>Returns a pointer to the AgentConfig object loaded from the passed in config file location</summary>
	///<param="AgentFile">The file location of the agent config object to find</param>
	///<returns>A pointer to the agent config object, or nullptr if it could not be found</returns>
	UAgentConfig* GetAgent(const FString AgentFile);

	UFUNCTION(BlueprintCallable)
	///<summary>Adds an agent to the scenario
	///<param="AgentFile">The string representation of the file location used for this Agent Config</param>
	///<param="AgentConfig">An optional Agent Config object if it is already loaded in memory</param>
	void AddAgent(const FString& AgentFile, UAgentConfig* AgentConfig = nullptr);

	UFUNCTION(BlueprintCallable)
	///<summary>Removes the selected agent config from this scenario</summary>
	///<param="AgentFile">The string representation of the file location of the Agent Config to remove</param>
	void RemoveAgentByFile(const FString& AgentFile);

	UFUNCTION(BlueprintCallable)
	///<summary>Removes the selected agent config from this scenario</summary>
	///<param="AgentConfig">The config object of the agent to remove.  Uses the FileLocation of the config object.</param>
	void RemoveAgentByObject(const UAgentConfig* AgentConfig);

	UFUNCTION(BlueprintPure)
	///<summary>Returns an array of names of the spawn points used with an agent config</summary>
	///<param="AgentConfig">The agent config to search with</param>
	///<returns>An array of names of the spawn points used with the agent config, or all if the parameter is nullptr</returns>
	TArray<FName> GetSpawnPoints(UAgentConfig* AgentConfig = nullptr) const;

	UFUNCTION(BlueprintCallable)
	///<summary>Returns the agent config object used at this spawn point</summary>
	///<param="SpawnName">The name of the spawn point to search with</summary>
	///<returns>The agent config object used at this spawn point or nullptr if it could not be found or loaded</returns>
	UAgentConfig* GetAgentBySpawn(FName SpawnName);

	UFUNCTION(BlueprintCallable)
	bool AddSpawn(FName SpawnName, UAgentConfig* Agent);

	bool ChangeAgentAtSpawn(FName SpawnName, UAgentConfig* NewAgent);

	void RemoveSpawn(FName SpawnName);

	void RemoveAllSpawnsOfAgent(UAgentConfig* Agent);
	
private:
	UPROPERTY(BlueprintGetter=GetMapName, BlueprintSetter=SetMapName)
	FName MapName;
	UPROPERTY()
	TMap<FString, UAgentConfig*> Agents;
	UPROPERTY()
	TMap<FName, FString> SpawnPoints;
};
