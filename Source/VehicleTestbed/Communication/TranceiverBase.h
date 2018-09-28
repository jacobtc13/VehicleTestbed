#pragma once

#include "Message.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TranceiverBase.generated.h"

UINTERFACE(MinimalAPI)
class UTranceiverBase : public UInterface
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API ITranceiverBase
{
	GENERATED_BODY()

public:
	virtual FVector GetLocation() const = 0;
};
