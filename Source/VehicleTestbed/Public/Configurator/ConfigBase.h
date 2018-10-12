#pragma once

#include "rapidxml.hpp"

#include "CoreMinimal.h"
#include "ConfigBase.generated.h"

UCLASS()
class VEHICLETESTBED_API UConfigBase : public UObject
{
	GENERATED_BODY()

public:
	UConfigBase();
	~UConfigBase();

	virtual rapidxml::xml_node<>* GetXMLNode();

};

