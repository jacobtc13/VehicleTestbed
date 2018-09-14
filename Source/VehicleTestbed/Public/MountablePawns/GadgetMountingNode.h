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
	UGadgetMountingNode();

	~UGadgetMountingNode();

	///<summary>Returns the pointer to the mounted gadget, can be nullptr</summary>
	///<returns>Pointer to mounted gadget</returns>
	AGadget* GetMountedGadget();

	///<summary>Sets the internal refrence for the mounted gadget</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted gadget</params>
	void SetMountedGadget(AGadget* toSetTo);

	///<summary>Sets the internal refrence for the mounted Pawn to nullptr</summary>
	void RemoveMountedGadget();

	///<summary>Calls the gadget's Activate method if there is a gadget attached</summary>
	void ActivateGadget();

	///<summary>Returns the name of the socket on the MountablePawn related to this node</summary>
	///<returns>FName of related socket</returns>
	FName GetRelatedSocketName();

private:
	UPROPERTY()
	///<summary>Internal reference to the Gadget mounted at this position</summary>
	AGadget* mountedGadget;

	///<summary>The name of the socket associated with this mounting node</summary>
	FName relatedSocketName;
};
