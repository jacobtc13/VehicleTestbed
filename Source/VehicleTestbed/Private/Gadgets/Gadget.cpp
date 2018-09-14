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
	return false;// (GetMountedMountingNode() != nullptr);
}

/*UGadgetMountingNode* AGadget::GetMountedMountingNode()
{
	return _mountedMountingNode;
}*/

/*void AGadget::SetMountedMountingNode(UGadgetMountingNode* toSetTo)
{
	_mountedMountingNode = toSetTo;
}*/

void AGadget::Activate()
{

}