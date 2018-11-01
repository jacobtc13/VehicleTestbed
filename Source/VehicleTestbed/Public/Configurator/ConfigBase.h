#pragma once

#include "Object.h"
#include "rapidxml.hpp"

#include "CoreMinimal.h"
#include "ConfigBase.generated.h"

UCLASS(Abstract, BlueprintType)
class VEHICLETESTBED_API UConfigBase : public UObject
{
	GENERATED_BODY()

public:
	UConfigBase();
	virtual ~UConfigBase();

	virtual rapidxml::xml_node<>* GetXMLNode() const;

	virtual bool InitializeFromXML(rapidxml::xml_document<>& doc);

	virtual bool Instantiate(UObject* ContextObject);

	UFUNCTION(BlueprintGetter)
	FString GetFileLocation() const;
	UFUNCTION(BlueprintSetter)
	void SetFileLocation(const FString& NewLocation);

protected:
	UPROPERTY(BlueprintGetter=GetFileLocation, BlueprintSetter=SetFileLocation)
	FString FileLocation;
};
