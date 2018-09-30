// Fill out your copyright notice in the Description page of Project Settings.

#include "CommDistributor.h"


// Add default functionality here for any ICommDistributor functions that are not pure virtual.
UCommDistributor::CommDistributor()
{

}

//Sends the message to the designated channel.
void Send(const FMessage<class T>&, UMessageSender sender, float frequency)
{
	//Check if there are any channels at all
	if (channelList.IsValidIndex)
	{
		if (channelList.Num != 0)
		{
			//Check if the channel exists
			for (ICommChannel::channel : UCommDistributor::channelList)
			{
				//Channel exists
				if (channel.GetFrequency == frequency)
				{
					//Send the message in that channel
					return;
				}
			}

			//Channel does not exist
			//TODO:Add functionality that adds a new Channel then send the message
		}
	}


}

void UCommDistributor::Add(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this method add new channels into the TArray
}

void UCommDistributor::Remove(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this Method Remove the channels from the TArray
}