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
	TScriptInterface<ISNRModel> SNRModel;
	UPROPERTY()
	TArray<IMessageReceiver*> ReceiverList;

public:
	UCommChannel();
	UCommChannel(float aFrequency, ISNRModel* aModel);
	float GetFrequency() const;
	void Broadcast(const IMessage& Message) const;
	void AddReceivers(TArray <IMessageReceiver*>& Input);
	void RemoveReceivers(TArray <IMessageReceiver*>& input);
	TArray<IMessageReceiver*> GetReceivers() const;
};
