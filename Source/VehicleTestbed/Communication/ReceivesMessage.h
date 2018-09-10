#pragma once

#include "TranceiverBase.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReceivesMessage.generated.h"

UINTERFACE(MinimalAPI)
class UReceivesMessage : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API IReceivesMessage : public ITranceiverBase
{
	GENERATED_BODY()

public:
	virtual void Receive(Message message, float SNR);
};
