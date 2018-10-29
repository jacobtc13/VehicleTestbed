#pragma once

#include "CoreMinimal.h"
#include "MessageReceiver.h"
#include "SNRModel.h"
#include "CommChannel.generated.h"

UCLASS()
class UCommChannel : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float Frequency;
	UPROPERTY()
	USNRModel* SNRModel;
	UPROPERTY()
	TArray<UObject*> ReceiverList;

public:
	UCommChannel();
	UCommChannel(float aFrequency, USNRModel* aModel);

	///<summary>Initializes the channel with a target frequency and propagation model</summary>
	///<param name="aFrequency">The frequency for this channel</param>
	///<param name="aModel">The SNR model to be used for this channel</param>
	void Initialize(float aFrequency, USNRModel* aModel);

	///<summary>Returns the frequency of this channel</summary>
	///<returns>The frequency of this channel</returns>
	float GetFrequency() const;

	///<summary>Broadcasts a message to all receivers of this frequency</summary>
	///<param name="Message">The message to be sent</param>
	///<param name="SignalPower">The power the signal is being broadcast at</param>
	///<param name="SenderPos">The position of the sender of the message</param>
	void Broadcast(const UMessage* Message, const float SignalPower, const FVector SenderPos) const;

	///<summary>Adds a list of receivers to this frequency</summary>
	///<param name="Receivers">The list of receivers</param>
	void AddReceivers(const TArray<UObject*>& Receivers);

	///<summary>Removes a list of receivers from this channel</summary>
	///<param name="Receivers">The list of receivers</param>
	void RemoveReceivers(const TArray<UObject*>& Receivers);

	///<summary>Returns the list of receivers on this frequency</summary>
	///<returns>The list of receivers</returns>
	TArray<UObject*> GetReceivers() const;
};
