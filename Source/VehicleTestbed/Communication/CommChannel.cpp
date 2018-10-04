// Fill out your copyright notice in the Description page of Project Settings.

#include "CommChannel.h"

ICommChannel::ICommChannel(float channel)
{
	ICommChannel::frequency = channel;
}

// Add default functionality here for any ICommChannel functions that are not pure virtual.

//Getters


float ICommChannel::GetFrequency()
{
	return ICommChannel::frequency;
}
