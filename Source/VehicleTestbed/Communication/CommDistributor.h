#pragma once

#include "Object.h"
#include <iostream>
//#include "CommDistributor.generated.h"
#include <list>
#include "CommChannel.h"
#include "SNRModel.h"
#include "Message.h"
#include "MessageSender.h"
#include "MessageReceiver.h"
#include "SNRModelFrequencyRange.h"

UCLASS()
class VEHICLETESTBED_API CommDistributor : public UObject
{
	GENERATED_BODY()

public:

	CommDistributor();
	void Send(const FMessage<class T>&, UMessageSender sender, float frequency);
	void Add(SNRModelFrequencyRange freqRange);
	void Remove(SNRModelFrequencyRange freqRange);

protected:
	TArray<CommChannel> channelList;
	SNRModel defaultPropModel;
	
};
