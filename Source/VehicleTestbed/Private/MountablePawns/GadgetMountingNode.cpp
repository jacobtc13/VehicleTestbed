// Fill out your copyright notice in the Description page of Project Settings.

#include "GadgetMountingNode.h"
#include "Engine/SkeletalMeshSocket.h"
#include "TestbedWheeledVehicle.h"


UGadgetMountingNode::UGadgetMountingNode()
{
}

UGadgetMountingNode::~UGadgetMountingNode()
{
}

AGadget* UGadgetMountingNode::GetMountedGadget()
{
	return MountedGadget;
}

void UGadgetMountingNode::SetMountedGadget(AGadget* Gadget)
{
	MountedGadget = Gadget;
}

void UGadgetMountingNode::ActivateGadget()
{
	if (MountedGadget != nullptr) MountedGadget->Activate();
}

USkeletalMeshSocket* UGadgetMountingNode::GetMeshSocket()
{
	return MeshSocket;
}

void UGadgetMountingNode::SetMeshSocket(USkeletalMeshSocket* Socket)
{
	MeshSocket = Socket;
}
