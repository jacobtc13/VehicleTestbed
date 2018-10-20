#pragma once

#include "Object.h"
#include "rapidxml.hpp"

#include "CoreMinimal.h"
#include "ConfigBase.generated.h"

UCLASS(BlueprintType)
class VEHICLETESTBED_API UConfigBase : public UObject
{
	GENERATED_BODY()

public:
	UConfigBase();
	virtual ~UConfigBase();

	virtual rapidxml::xml_node<>* GetXMLNode();

	virtual bool InitializeFromXML(rapidxml::xml_document<>& doc);

	UFUNCTION(BlueprintGetter)
	FString GetFileLocation() const;
	UFUNCTION(BlueprintSetter)
	void SetFileLocation(const FString& NewLocation);

protected:
	UPROPERTY(BlueprintGetter=GetFileLocation, BlueprintSetter=SetFileLocation)
	FString FileLocation;
};
