// Fill out your copyright notice in the Description page of Project Settings.

#include "CommDistributor.h"


// Add default functionality here for any ICommDistributor functions that are not pure virtual.
ICommDistributor::ICommDistributor()
{

}

//Sends the message to the designated channel.
void ICommDistributor::Send(const FMessage<class T>& message, UMessageSender sender, float variance)
{
	//TODO: Need to talk to Matt about getting the sender's frequency
	if (CheckForMultiChannels(sender.getFrequency, variance))
	{
		for (ICommChannel channel : GetChannels(sender.getFrequency, variance))
		{
			//Broadcast message
		}
	}
	//No channels exist within range, Perhaps log an event?
}

//Adds a UMessageReceiver to a specific channel, Also creates a channel non-existant
void ICommDistributor::AddToChannel(float frequency, UMessageReceiver receiver)
{
	//Channel does not exist
	if (!CheckForChannel(frequency))
	{
		CreateChannel(frequency);
	}
	for (ICommChannel channel : GetChannels(frequency, 0))
	{
		//package the input reciever into a TArray of UMessageReceivers
		TArray<UMessageReceiver> temp;
		temp.AddUnique(receiver);

		channel.AddReceivers(temp);
	}
}
	
//Removes UMessageReceiver from a specific Channel
void ICommDistributor::RemoveFromChannel(float frequency, UMessageReceiver receiver)
{
	for (ICommChannel channel : GetChannels(frequency, 0))
	{
		//package the input reciever into a TArray of UMessageReceivers
		TArray<UMessageReceiver> temp;
		temp.AddUnique(receiver);

		channel.RemoveReceivers(temp);
	}
}

//Checks if a single channel exist
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

//Returns true if a single channel exists within a range of frequencies
bool ICommDistributor::CheckForMultiChannels(float frequency, float variance)
{
	float upperRange = frequency + variance;
	float lowerRange = frequency - variance;
	if (channelList.IsValidIndex)
	{
		if (channelList.Num != 0)
		{
			for (ICommChannel channel : channelList)
			{
				if (channel.GetFrequency() >= lowerRange && channel.GetFrequency() <= upperRange)
				{
					return true;
				}
			}
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