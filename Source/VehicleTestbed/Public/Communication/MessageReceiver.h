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
	///<summary>Receives a message with a signal to noise ratio</summary>
	///<param name="message">The message being received</param>
	///<param name="SNR">The signal to noise ratio</param>
	virtual void Receive(const IMessage& message, float SNR) = 0;

	///<summary>Initializes the receiver with a minimum SNR</summary>
	///<param name="aMinSNR">The minimum SNR at which this receiver can interpet messages</param>
	virtual void Initialization(float aMinSNR);

	///<summary>Returns the frequency this receiver is listening to</summary>
	///<returns>The frequency</returns>
	float GetFrequency() const;

	///<summary>Sets the frequency this receiver is listening to</summary>
	///<param name="NewFrequency">The new frequency to listen to</param>
	void SetFrequency(const float NewFrequency);

	enum EResponseCode
	{
		Received,
		Garbled
	};

protected:
	float Frequency;
	float MinSNR;
};
