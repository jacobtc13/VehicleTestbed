// Fill out your copyright notice in the Description page of Project Settings.

#include "CommChannel.h"

ICommChannel::ICommChannel(float channel)
{
	ICommChannel::frequency = channel;
}

//Adds a reciever to the channel
void ICommChannel::AddReceivers(TArray <UMessageReceiver> input)
{
	for (auto& var : input)
	{
		receivers.AddUnique(var);
	}
}

void ICommChannel::RemoveReceivers(TArray <UMessageReceiver> input)
{
	for (auto& var : input)
	{
		receivers.Remove(var);
	}
}

//TODO: Make a method that distributes message to the receivers



// Add default functionality here for any ICommChannel functions that are not pure virtual.

//Getters

float ICommChannel::GetFrequency()
{
	return ICommChannel::frequency;
}
