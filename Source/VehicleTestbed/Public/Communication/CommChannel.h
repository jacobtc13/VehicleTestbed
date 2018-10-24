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

	void Initialize(float aFrequency, USNRModel* aModel);

	float GetFrequency() const;
	void Broadcast(const IMessage& Message, const FVector SenderPos) const;
	void AddReceivers(const TArray<UObject*>& Receivers);
	void RemoveReceivers(const TArray<UObject*>& Receivers);
	TArray<UObject*> GetReceivers() const;
};
