#pragma once

#include "CoreMinimal.h"

#include "CommChannel.h"
#include "SNRModel.h"
#include "SNRModelFrequencyRange.h"
#include "Message.h"
#include "MessageSender.h"
#include "MessageReceiver.h"

#include "CommDistributor.generated.h"

UCLASS(Abstract)
class VEHICLETESTBED_API UCommDistributor : public UObject
{
	GENERATED_BODY()

public:
	static void Send(const IMessage& Message, UObject* Sender, float Frequency);
	static void AddToChannel(float Frequency, UObject* Receiver);
	static void RemoveFromChannel(float Frequency, UObject* Receiver);
	static bool CheckForChannel(float Frequency);
	static bool CheckForMultiChannels(float Frequency, float Variance);
	static void CreateChannel(float Frequency);
	static TArray<UCommChannel*> GetChannels(float Frequency, float Variance);
	static void SwitchChannel(float Frequency, UObject* Receiver);
	static TArray<USNRModelFrequencyRange*> RetrieveSNRRange(float Frequency);

	// TODO: Add some way to initialize variables

protected:
	static TArray<UCommChannel*> ChannelList;
	static TArray<USNRModelFrequencyRange*> PropagateList;
	static USNRModel* DefaultProp;
};
