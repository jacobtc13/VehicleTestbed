#pragma once

#include "Object.h"
#include "rapidxml.hpp"

#include "CoreMinimal.h"
#include "ConfigBase.generated.h"

UCLASS()
class VEHICLETESTBED_API UConfigBase : public UObject
{
	GENERATED_BODY()

public:
	UConfigBase();
	virtual ~UConfigBase();

	virtual rapidxml::xml_node<>* GetXMLNode();

	FString GetFileLocation() const;
	void SetFileLocation(const FString& NewLocation);

protected:
	FString FileLocation;
};
