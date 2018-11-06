#pragma once

#include "rapidxml.hpp"
#include "ConfigBase.h"
#include "TestbedPlayerController.h"
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

	FName GetAgentClassName() const;

	void SetAgentClassName(const FName& NewClassName);

	FName GetAgentName() const;

	void SetAgentName(const FName& NewAgentName);



private:
	UPROPERTY()
	FName AgentClassName;

	UPROPERTY()
	FName AgentName;

	UPROPERTY()
	ATestbedPlayerController* Controller;

	static TArray<TSubclassOf<AGadget>> Gadgets;

private:
	void InitializeGadgetsMap();
};
