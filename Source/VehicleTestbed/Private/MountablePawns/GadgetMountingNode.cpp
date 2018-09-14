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

void UGadgetMountingNode::SetMountedGadget(AGadget* toSetTo)
{
	_mountedGadget = toSetTo;
}

/*AMountablePawn* UGadgetMountingNode::GetMountedPawn()
{
	return _mountedPawn;
}*/

void UGadgetMountingNode::ClearMountedGadget()
{
	//_mountedGadget->SetMountedMountingNode(nullptr);
	SetMountedGadget(nullptr);
}

FName UGadgetMountingNode::GetRelatedSocketName()
{
	return _relatedSocketName;
}
