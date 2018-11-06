#pragma once

#include "rapidxml.hpp"
#include "ConfigBase.h"
#include "TestbedPlayerController.h"

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS(BlueprintType)
class VEHICLETESTBED_API UAgentConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const override;

	virtual bool InitializeFromXML(rapidxml::xml_document<>& doc) override;

	UFUNCTION(meta = (WorldContext = ContextObject))
	virtual bool Instantiate(UObject* ContextObject) override;

protected:
	UPROPERTY()
	UClass* AgentClass;

	UPROPERTY()
	FString AgentName;

	UPROPERTY()
	ATestbedPlayerController* Controller;

	UPROPERTY()
	TMap<FString, FString> Properties;

	// TODO: Redefine this as sub class of gadgets
	static TMap<FName, UClass*> Gadgets;
};

