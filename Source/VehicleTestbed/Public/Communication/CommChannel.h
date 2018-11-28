#pragma once

#include "CoreMinimal.h"
#include "MessageReceiver.h"
#include "SNRModel.h"
#include "CommChannel.generated.h"

UCLASS(BlueprintType)
class UCommChannel : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintGetter=GetFrequency)
	float Frequency;
	UPROPERTY(BlueprintGetter=GetSNRModel, BlueprintSetter=SetSNRModel)
	USNRModel* SNRModel;
	UPROPERTY(BlueprintGetter=GetReceivers)
	TArray<UObject*> ReceiverList;

public:
	///<summary>Default constructor</summary>
	UCommChannel();

	UFUNCTION(BlueprintCallable)
	///<summary>Initializes the channel with a target frequency and propagation model</summary>
	///<param name="aFrequency">The frequency for this channel</param>
	///<param name="aModel">The SNR model to be used for this channel</param>
	void Initialize(float aFrequency, USNRModel* aModel);

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the frequency of this channel</summary>
	///<returns>The frequency of this channel</returns>
	float GetFrequency() const;

	UFUNCTION(BlueprintCallable)
	///<summary>Broadcasts a message to all receivers of this frequency</summary>
	///<param name="Message">The message to be sent</param>
	///<param name="SignalPower">The power the signal is being broadcast at</param>
	///<param name="SenderPos">The position of the sender of the message</param>
	void Broadcast(const UMessage* Message, const float SignalPower, const FVector SenderPos) const;

	UFUNCTION(BlueprintCallable)
	///<summary>Adds a list of receivers to this frequency</summary>
	///<param name="Receivers">The list of receivers</param>
	void AddReceivers(const TArray<UObject*>& Receivers);

	UFUNCTION(BlueprintCallable)
	///<summary>Removes a list of receivers from this channel</summary>
	///<param name="Receivers">The list of receivers</param>
	void RemoveReceivers(const TArray<UObject*>& Receivers);

	UFUNCTION(BlueprintGetter)
	///<summary>Returns the list of receivers on this frequency</summary>
	///<returns>The list of receivers</returns>
	TArray<UObject*> GetReceivers() const;

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the SNR model of this channel</summary>
	///<returns>The SNR model of this channel</returns>
	USNRModel* GetSNRModel() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the SNR model of this channel</summary>
	///<param name="NewSNRModel">The new SNR model to use</param>
	void SetSNRModel(USNRModel* NewSNRModel);
};
