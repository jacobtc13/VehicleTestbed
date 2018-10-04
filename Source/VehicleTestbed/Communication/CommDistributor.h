// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CommChannel.h"
#include "SNRModel.h"
#include "SNRModelFrequencyRange.h"
#include "Message.h"
#include "MessageSender.h"
#include "MessageReceiver.h"

#include "CommDistributor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommDistributor : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
static class VEHICLETESTBED_API ICommDistributor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
	public:
		ICommDistributor();
		void Send(const FMessage<class T>&, UMessageSender sender, float frequency);
		void AddToChannel(float frequency, UMessageReceiver receiver);
		void RemoveFromChannel(float frequency, UMessageReceiver receiver);
		bool CheckForChannel(float frequency);
		void CreateChannel(float frequency);
		ICommChannel GetChannels(float frequency, float variance);

	protected:
		TArray<ICommChannel> channelList;
		//SNRModel defaultPropModel;
	
};