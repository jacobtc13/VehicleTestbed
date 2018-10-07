// Fill out your copyright notice in the Description page of Project Settings.

#include "CommDistributor.h"


// Add default functionality here for any ICommDistributor functions that are not pure virtual.
ICommDistributor::ICommDistributor()
{

}

//Sends the message to the designated channel.
void ICommDistributor::Send(const FMessage<class T>& message, UMessageSender sender, float variance)
{
	//TODO: Create functionality

}

//Creates a channel, if required, and adds that reciever to that channel
void ICommDistributor::AddToChannel(float frequency, UMessageReceiver receiver)
{
	//TODO: Make this method add new channels into the TArray
	//Channel does not exist
	if (!CheckForChannel(frequency))
	{
		CreateChannel(frequency);
	}
	for (ICommChannel channel : GetChannels(frequency, 0))//TODO: workout how to get the GETCHANNELs here
	{
		//TODO: add reciever to the newly created channel
	}
}
	
//TODO: Make a method that removes Recievers from channels

void ICommDistributor::RemoveFromChannel(float frequency, UMessageReceiver receiver)
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
			for (ICommChannel channel : channelList)
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

//Creates a channel and adds it to the list of channels
void ICommDistributor::CreateChannel(float frequency)
{
	channelList.AddUnique(ICommChannel(frequency));
}

//Retrieves an array of channels that are in the frequency range
TArray<ICommChannel> ICommDistributor::GetChannels(float frequency, float variance)
{
	TArray<ICommChannel> output;
	float upperRange = frequency + variance;
	float lowerRange = frequency - variance;
	for (ICommChannel channel : channelList)
	{
		if (channel.GetFrequency() >= lowerRange  && channel.GetFrequency() <= upperRange)
		{
			output.Add(channel);
		}
	}
	return output;
}