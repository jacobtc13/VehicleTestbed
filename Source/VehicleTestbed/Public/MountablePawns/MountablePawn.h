// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GadgetMountingNode.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MountablePawn.generated.h"

UINTERFACE(MinimalAPI)
///<summary>This is an interface that allows any class that uses it to have gadgets attached to their sockets on their skeletal mesh</summary>
class UMountablePawn : public UInterface
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API IMountablePawn
{
	GENERATED_BODY()

public:
	UFUNCTION()
	///<summary>Get a TArray of pointers to the UGadgetMouningNodes on the vehicle</summary>
	///<returns>A TArray of pointers to the UGadgetMountingNodes</returns>
	virtual TArray<UGadgetMountingNode*> GetMountingNodes() = 0;

	UFUNCTION()
	///<summary>Search for and returns a GadgetMountingNode that is associated with a socket name. Can return a nullptr if nothing is found</summary>
	///<params name = 'SocketName'>The socket name that is associated with the GadgetMountingNode being searched for</params>
	///<returns>The GadgetMountingNode that is associated with the SocketName</returns>
	virtual UGadgetMountingNode* GetMountingNodeBySocketName(FName SocketName) = 0;

	UFUNCTION()
	///<summary> GadgetMountingNodes related to the socket denoted by FName toAddTo</summary>
	///<params name = 'GadgetClass'>A static class of the gadget that will be attached to the pawn</params>
	///<params name = 'Socket'>The socket on the skeletal mesh of the pawn</params>
	virtual void MountGadget(TSubclassOf<AGadget> GadgetClass, USkeletalMeshSocket* Socket) = 0;
};
