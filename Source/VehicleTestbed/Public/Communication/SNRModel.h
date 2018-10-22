#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MessageSender.h"
#include "MessageReceiver.h"
#include "SNRModel.generated.h"

UINTERFACE(MinimalAPI)
class USNRModel : public UInterface
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API ISNRModel
{
	GENERATED_BODY()

public:
	virtual float CalculateSNR(IMessageSender* Sender, IMessageReceiver* Receiver) const = 0;
};
