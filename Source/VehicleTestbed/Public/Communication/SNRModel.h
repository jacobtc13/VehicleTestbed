#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "MessageSender.h"
#include "MessageReceiver.h"
#include "SNRModel.generated.h"

UCLASS(Abstract)
class USNRModel : public UObject
{
	GENERATED_BODY()

public:
	virtual float CalculateSNR(const FVector& SenderPos, const FVector& ReceiverPos) const
	{
		check(0 && "You must override this")
	}
};
