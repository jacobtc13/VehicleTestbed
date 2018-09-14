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
	return mountedGadget;
}

void UGadgetMountingNode::SetMountedGadget(AGadget* toSetTo)
{
	mountedGadget = toSetTo;
}

void UGadgetMountingNode::RemoveMountedGadget()
{
	SetMountedGadget(nullptr);
}

void UGadgetMountingNode::ActivateGadget()
{
	if (mountedGadget != nullptr) mountedGadget->Activate();
}

FName UGadgetMountingNode::GetRelatedSocketName()
{
	return relatedSocketName;
}
