// Fill out your copyright notice in the Description page of Project Settings.

#include "CommDistributor.h"


// Add default functionality here for any ICommDistributor functions that are not pure virtual.
ICommDistributor::CommDistributor()
{

}

//Sends the message to the designated channel.
void ICommDistributor::Send(const FMessage<class T>&, UMessageSender sender, float frequency)
{
	if (CheckChannel(frequency))
	{

	}
}

void ICommDistributor::Add(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this method add new channels into the TArray

}

void ICommDistributor::Remove(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this Method Remove the channels from the TArray
}

bool ICommDistributor::CheckForChannel(float frequency)
{
	//Check if there are any channels at all
	if (channelList.IsValidIndex)
	{
		if (channelList.Num != 0)
		{
			//Check if the channel exists
			for (ICommChannel::channel : ICommDistributor::channelList)
			{
				//Channel exists
				if (channel.GetFrequency == frequency)
				{
					return true;
				}
			}
			//Channel does not exist
		}
	}
	return false;
}