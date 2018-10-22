#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "SNRModel.h"
#include "VoidSNR.generated.h"

UCLASS()
class UVoidSNR : public UObject, public ISNRModel
{
	GENERATED_BODY()

public:
	float CalculateSNR(IMessageSender* Sender, IMessageReceiver* Receiver) const override;
};
