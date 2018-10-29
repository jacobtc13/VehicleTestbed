#pragma once

#include "Message.h"
#include "EventRecorder.h"

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
	///<summary>Returns the location of this object</summary>
	///<returns>The location of this object</returns>
	virtual FVector GetLocation() const = 0;
};
