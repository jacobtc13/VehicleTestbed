#pragma once

#include "rapidxml.hpp"
#include "ConfigBase.h"
#include "TestbedPlayerController.h"
#include "TestbedWheeledVehicle.h"
#include "Gadget.h"

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS(BlueprintType)
class VEHICLETESTBED_API UAgentConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	///<summary>Attaches the xml structure which represents this config to the document</summary>
	///<param name="OutDocument">The xml document to append to</param>
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const override;

	///<summary>Initializes this config object from an xml document</summary>
	///<param name="Document">The xml document to initialize from</param>
	///<returns>Whether this config object initialized correctly</returns>
	virtual bool InitializeFromXML(rapidxml::xml_document<>& Document) override;

	UFUNCTION(meta = (WorldContext = ContextObject))
	///<summary>Creates, initializes and spawns the agent represented by this config into the game world</summary>
	///<param name="ContextObject">A UObject which can provide world context</name>
	///<returns>Whether this config object was able to instantiate correctly</returns>
	virtual bool Instantiate(UObject* ContextObject) override;

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the UClass used for this agent</summary>
	///<returns>The UClass of this agent</returns>
	UClass* GetAgentClass() const;

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the name of the UClass used by this agent</summary>
	///<returns>The name of the UClass of this agent</returns>
	FName GetAgentClassName() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the name of the UClass used by this agent</summary>
	///<param name="NewClassName">The name of the new UClass for this agent</param>
	void SetAgentClassName(const FName& NewClassName);

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the name of this agent</summary>
	///<returns>The FName representation of the name of this agent</returns>
	FName GetAgentName() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the name of this agent</summary>
	///<param name="NewAgentName">The new name of this agent</param>
	void SetAgentName(const FName& NewAgentName);

	UFUNCTION(BlueprintGetter)
	///<summary>Gets whether to possess this agent when the game starts</summary>
	///<returns>Whether to possess this agent or not</returns>
	bool GetPossessAtStart() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets whether to possess this agent when the game starts</summary>
	///<param name="ShouldPossessAtStart">Whether to possess this agent</param>
	void SetPossessAtStart(const bool ShouldPossessAtStart);

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the names of the gadgets on this agent</summary>
	///<returns>An array of names of gadgets</returns>
	TArray<FName> GetGadgetsOnThisAgent() const;

	UFUNCTION(BlueprintCallable)
	///<summary>Adds a gadget to this agent by name.  Checks if the gadget name is valid and will not add it if it is not.</summary>
	///<param name="GadgetName">The name of the gadget to add</param>
	void AddGadget(const FName& GadgetName);

	UFUNCTION(BlueprintCallable)
	///<summary>Removes a gadget from this agent by name</summary>
	///<param name="GagdetName">The name of the gadget to remove</param>
	void RemoveGadget(const FName& GadgetName);

	UFUNCTION(BlueprintCallable)
	///<summary>Sets the next spawn position to use when instantiating this agent</summary>
	///<param name="NextPosition">The coordinates to spawn at</param>
	///<param name="NextRotation">The rotation to spawn at</param>
	void SetNextSpawn(const FVector& NextPosition, const FRotator& NextRotation);

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the names of all available agent classes using the reflection system</summary>
	///<returns>An array of names of agent classes</returns>
	static TArray<FName> GetAgentClassNames();

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the names of all available gadget classes using the reflection system</summary>
	///<returns>An array of names of gadget classes</returns>
	static TArray<FName> GetGadgetClassNames();

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the UClass of all available gadget classes using the reflection system</summary>
	///<returns>An array of the UClasses of gadget classes</returns>
	static TArray<TSubclassOf<AGadget>> GetGadgetClasses();

private:
	UPROPERTY(BlueprintGetter=GetAgentClassName, BlueprintSetter=SetAgentClassName)
	FName AgentClassName;

	UPROPERTY(BlueprintGetter=GetAgentName, BlueprintSetter=SetAgentName)
	FName AgentName;

	UPROPERTY(BlueprintGetter=GetPossessAtStart, BlueprintSetter=SetPossessAtStart)
	bool bPosessAtStart;

	UPROPERTY(BlueprintGetter=GetGadgetsOnThisAgent)
	TArray<FName> GadgetsOnThisAgent;

	UPROPERTY()
	FVector PositionforNextSpawn;

	UPROPERTY()
	FRotator RotationForNextSpawn;

	static TArray<TSubclassOf<ATestbedWheeledVehicle>> AgentClasses;
	static TArray<TSubclassOf<AGadget>> Gadgets;

private:
	///<summary>Uses the reflection system to fill the AgentClasses array with all subclasses of ATestbedWheeledVehicle</summary>
	static void InitializeAgentClassArray();

	///<summary>Uses the reflection system to fill the Gadgets array with all subclasses of AGadget</summary>
	static void InitializeGadgetsArray();
};
