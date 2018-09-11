// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"

AGadget::AGadget()
{
}

AGadget::~AGadget()
{
}

bool AGadget::IsMounted()
{
	return (GetMountedMountingNode() != nullptr);
}

UGadgetMountingNode *AGadget::GetMountedMountingNode()
{
	_mutexMountedMountingNode.lock();

	UGadgetMountingNode *result = _mountedMountingNode;

	_mutexMountedMountingNode.unlock();

	return result;
}

int AGadget::SetMountedMountingNode(UGadgetMountingNode *toSetTo)
{
	int result = 0;

	_mutexMountedMountingNode.lock();

	//Assume success for these return codes
	if (IsMounted())
	{
		result = 1;//Successfully set from non-null reference
	}

	else
	{
		result = 0;//Successfully set from null refrence
	}

	_mountedMountingNode = toSetTo;

	_mutexMountedMountingNode.unlock();

	return result;
}
