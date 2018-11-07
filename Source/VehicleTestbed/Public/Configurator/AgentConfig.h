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
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const override;

	virtual bool InitializeFromXML(rapidxml::xml_document<>& Document) override;

	UFUNCTION(meta = (WorldContext = ContextObject))
	virtual bool Instantiate(UObject* ContextObject) override;

	static TArray<FName> GetAgentClassNames();

	FName GetAgentClassName() const;

	void SetAgentClassName(const FName& NewClassName);

	FName GetAgentName() const;

	void SetAgentName(const FName& NewAgentName);

	bool GetPossessAtStart() const;

	void SetPossessAtStart(const bool ShouldPossessAtStart);

	TArray<FName> GetGadgetsOnThisAgent() const;

	void AddGadget(const FName& GadgetName);

	void RemoveGadget(const FName& GadgetName);

	ATestbedWheeledVehicle* GetAgent() const;

private:
	UPROPERTY()
	FName AgentClassName;

	UPROPERTY()
	FName AgentName;

	UPROPERTY()
	bool bPosessAtStart;

	UPROPERTY()
	TArray<FName> GadgetsOnThisAgent;

	UPROPERTY()
	ATestbedWheeledVehicle* Agent;

	static TArray<TSubclassOf<ATestbedWheeledVehicle>> AgentClasses;
	static TArray<TSubclassOf<AGadget>> Gadgets;

private:
	static void InitializeAgentClassArray();
	static void InitializeGadgetsArray();
};
