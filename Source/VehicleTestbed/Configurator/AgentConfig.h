#pragma once

#include "CoreMinimal.h"
#include "AgentConfig.generated.h"

UCLASS()
class VEHICLETESTBED_API UAgentConfig : public UObject
{
	GENERATED_BODY()

public:
	UAgentConfig();
	~UAgentConfig();
protected:
	UClass * AgentClass;
};

