// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.h"
#include "GadgetMountingNode.generated.h"

/**
 * This class represents the socket on the skeletal mesh of the vehicle that will have a gadget attached
 */
UCLASS()
class VEHICLETESTBED_API UGadgetMountingNode : public UObject
{
	GENERATED_BODY()

public:
	///<summary>Default Constructor</summary>
	UGadgetMountingNode();

	///<summary>Default Deconstructor</summary>
	~UGadgetMountingNode();

	///<summary>Returns the pointer to the mounted gadget, can be nullptr</summary>
	///<returns>Pointer to mounted gadget</returns>
	AGadget* GetMountedGadget();

	///<summary>Sets the internal refrence for the mounted gadget</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted gadget</params>
	void SetMountedGadget(AGadget* Gadget);

	///<summary>Calls the gadget's Activate method if there is a gadget attached</summary>
	void ActivateGadget();

	///<summary>Returns the name of the socket on the MountablePawn related to this node</summary>
	///<returns>FName of related socket</returns>
	USkeletalMeshSocket* GetMeshSocket();

	///<summary>Sets the SkeletalMeshSocket for the GadgetMountingNode</summary>
	///<params name='Socket'>Pointer to the SkeletalMeshSocket that will be set</params>
	void SetMeshSocket(USkeletalMeshSocket* Socket);

private:
	UPROPERTY()
	///<summary>Internal reference to the Gadget mounted at this position</summary>
	AGadget* MountedGadget;

	UPROPERTY()
	///<summary>The name of the socket associated with this mounting node</summary>
	USkeletalMeshSocket* MeshSocket;
};
