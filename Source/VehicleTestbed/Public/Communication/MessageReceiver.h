#pragma once

#include "TranceiverBase.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MessageReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UMessageReceiver : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API IMessageReceiver : public ITranceiverBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	///<summary>Receives a message with a signal to noise ratio</summary>
	///<param name="Message">The message being received</param>
	///<param name="SNR">The signal to noise ratio</param>
	virtual void Receive(const UMessage* Message, float SNR) = 0;

	UFUNCTION()
	///<summary>Returns the frequency this receiver is listening to</summary>
	///<returns>The frequency</returns>
	virtual float GetFrequency() const = 0;

	UFUNCTION()
	///<summary>Sets the frequency this receiver is listening to</summary>
	///<param name="NewFrequency">The new frequency to listen to</param>
	virtual void SetFrequency(const float NewFrequency) = 0;

	UFUNCTION()
	///<summary>Gets the minimum SNR at which this receiver can understand messages</summary>
	///<returns>The minimum SNR</returns>
	virtual float GetMinSNR() const = 0;

	UFUNCTION()
	///<summary>Sets the minimum SNR at which this receiver can understand messages</summary>
	///<param name="NewMinSNR">The minimum SNR</param>
	virtual void SetMinSNR(const float NewMinSNR) = 0;
};
