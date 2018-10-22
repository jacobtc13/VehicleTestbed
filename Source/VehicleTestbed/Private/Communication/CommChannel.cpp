// Fill out your copyright notice in the Description page of Project Settings.

#include "CommChannel.h"

ICommChannel::ICommChannel(float channel, ISNRModel model)
{
	ICommChannel::frequency = channel;
}

//Adds a reciever to the channel
void ICommChannel::AddReceivers(TArray <UMessageReceiver> input)
{
	for (auto& var : input)
	{
		receiverList.AddUnique(var);
	}
}

void ICommChannel::RemoveReceivers(TArray <UMessageReceiver> input)
{
	for (auto& var : input)
	{
		receiverList.Remove(var);
	}
}

//Gives each receiver in the channel the message.
//TODO: Make a method that distributes message to the receivers
void ICommChannel::Broadcast(const FMessage<class T>& message)
{
	//Check if there are receivers in the list
	if (GetReceivers().Num > 0)
	{
		for (UMessageReceiver& receiver : GetReceivers())
		{
			//Pass message to receiver here
		}
	}
	else
	{
		//Log event - message was not broadcast to any receiver.
	}
	
}


// Add default functionality here for any ICommChannel functions that are not pure virtual.

//Getters

float ICommChannel::GetFrequency()
{
	return ICommChannel::frequency;
}

TArray<UMessageReceiver> ICommChannel::GetReceivers()
{
	return receiverList;
}
