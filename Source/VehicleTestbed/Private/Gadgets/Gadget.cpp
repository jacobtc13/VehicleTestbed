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

UGadgetMountingNode* AGadget::GetMountedMountingNode()
{
	return _mountedMountingNode;
}

int AGadget::SetMountedMountingNode(UGadgetMountingNode* toSetTo)
{
	int result = 0;

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

	return result;
}

bool operator == (const AGadget A, const AGadget B)
{
	//Two AGadgets can only be considered equivilant if they are the same object, represented here as having the same memory address
	return (&A == &B);
}
