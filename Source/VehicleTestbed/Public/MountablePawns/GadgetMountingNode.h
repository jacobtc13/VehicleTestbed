// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.h"
#include "MountablePawn.h"
#include "GadgetMountingNode.generated.h"

/**
 * This class acts to link a AMountablePawn and a AGadget which is mounted to it
 */
UCLASS()
class VEHICLETESTBED_API UGadgetMountingNode : public UObject
{
	GENERATED_BODY()

private:
	///<summary>Internal reference to the Gadget mounted at this position</summary>
	AGadget* _mountedGadget;

	///<summary>Internal reference to the Pawn this is mounted on </summary>
	//AMountablePawn* _mountedPawn;

	///<summary>The name of the socket associated with this mounting node</summary>
	FName _relatedSocketName;

public:
	UGadgetMountingNode();
	~UGadgetMountingNode();

	///<summary>Returns the pointer to the mounted gadget, can be nullptr</summary>
	///<returns>Pointer to mounted gadget</returns>
	AGadget* GetMountedGadget();

	///<summary>Sets the internal refrence for the mounted gadget</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted gadget</params>
	void SetMountedGadget(AGadget* toSetTo);

	///<summary>Returns the pointer to the mounted Pawn, can be nullptr</summary>
	///<returns>Pointer to mounted Pawn</returns>
	//AMountablePawn* GetMountedPawn();

	///<summary>Sets the internal refrence for the mounted Pawn to nullptr</summary>
	void ClearMountedGadget();

	///<summary>Returns the name of the socket on the MountablePawn related to this node</summary>
	///<returns>FName of related socket</returns>
	FName GetRelatedSocketName();
};
