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

	UFUNCTION()
	///<summary>Returns an array of the file locations of the agent configs used in this scenario</summary>
	///<returns>An array of file locations of the agents configs used in this scenario</returns>
	TArray<FString> GetAgentFileLocations() const;
	UFUNCTION()
	///<summary>Returns an array of Agent Config objects used by this scenario, creating them from file if they don't exist in memory</summary>
	///<returns>An array of Agent Config objects used by this scenario</returns>
	TArray<UAgentConfig*> GetAgents();

	UFUNCTION()
	///<summary>Returns the name of the map used in this scenario</summmary>
	///<returns>The name of the map uesd in this scenario</returns>
	FName GetMapName() const;
	UFUNCTION()
	///<summary>Sets the name of the map used for this scenario</summary>
	///<param="NewMapName">The name of the new map used for this scenario</param>
	void SetMapName(FName NewMapName);

private:
	TMap<FString, UAgentConfig*> Agents;
	// TODO: Spawn points
	FName MapName;
};
