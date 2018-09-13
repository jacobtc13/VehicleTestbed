// Fill out your copyright notice in the Description page of Project Settings.

#include "GadgetMountingNode.h"


UGadgetMountingNode::UGadgetMountingNode()
{
}

UGadgetMountingNode::~UGadgetMountingNode()
{
}

AGadget* UGadgetMountingNode::GetMountedGadget()
{
	return _mountedGadget;
}

int UGadgetMountingNode::SetMountedGadget(AGadget* toSetTo)
{
	int result = 0;

	//Assume success for these return codes
	if (_mountedGadget != nullptr)
	{
		result = 1;//Successfully set from non-null reference
	}

	else
	{
		result = 0;//Successfully set from null refrence
	}

	_mountedGadget = toSetTo;

	return result;
}

AMountablePawn* UGadgetMountingNode::GetMountedPawn()
{
	return _mountedPawn;
}

int UGadgetMountingNode::SetMountedPawn(AMountablePawn* toSetTo)
{
	int result = 0;

	//Assume success for return codes
	if (_mountedPawn != nullptr)
	{
		result = 1;//Successfully set from non-null reference
	}

	else
	{
		result = 0;//Successfully set from null refrence
	}

	_mountedPawn = toSetTo;

	return result;
}

int UGadgetMountingNode::ClearMountedGadget()
{
	return SetMountedGadget(nullptr);
}

FName UGadgetMountingNode::GetRelatedSocketName()
{
	return _relatedSocketName;
}

void UGadgetMountingNode::SetRelatedSocketName(FName toSetTo)
{
	_relatedSocketName = toSetTo;
}
