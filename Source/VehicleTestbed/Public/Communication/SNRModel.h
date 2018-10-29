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
	///<summary>Calculates the SNR between two positions</summary>
	///<param name="SignalPower">The power the signal is broadcast at</param>
	///<param name="SenderPos">The position of the sender of the message</param>
	///<param name="ReceiverPos">The position of the receiver of the message</param>
	///<returns>The calculated SNR in decibels</returns>
	virtual float CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const
	{
		check(0 && "You must override this");
		return 0;
	}
};
