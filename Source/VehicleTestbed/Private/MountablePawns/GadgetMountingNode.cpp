// Fill out your copyright notice in the Description page of Project Settings.

#include "GadgetMountingNode.h"

#include "TestbedWheeledVehicle.h"


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

AGadget* UGadgetMountingNode::SetMountedGadget(TSubclassOf<AGadget> GadgetClass, ATestbedWheeledVehicle* AttachingVehicle)
{
	
	// TODO: change the FVector
	return nullptr;

}

void UGadgetMountingNode::RemoveMountedGadget()
{
	//SetMountedGadget(nullptr);
}

void UGadgetMountingNode::ActivateGadget()
{
	if (mountedGadget != nullptr) mountedGadget->Activate();
}

FName UGadgetMountingNode::GetSocketName()
{
	return relatedSocketName;
}

void UGadgetMountingNode::SetSocketName(FName SocketName)
{
	relatedSocketName = SocketName;
}
