#pragma once

#include "ConfigBase.h"

#include "CoreMinimal.h"
#include "CommConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UCommConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const override;

	virtual bool InitializeFromXML(rapidxml::xml_document<>& doc) override;

	virtual bool Instantiate(UObject* ContextObject) override;

private:

};
