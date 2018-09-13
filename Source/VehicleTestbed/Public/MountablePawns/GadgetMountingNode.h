// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//forward refrences

class AGadget;
class AMountablePawn;

#include "CoreMinimal.h"
#include "GadgetMountingNode.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETESTBED_API UGadgetMountingNode : public UObject
{
	GENERATED_BODY()

private:
	///<summary>Internal reference to the Gadget mounted at this position</summary>
	AGadget* _mountedGadget = nullptr;

	///<summary>Internal reference to the Pawn this is mounted on </summary>
	AMountablePawn* _mountedPawn = nullptr;

public:
	UGadgetMountingNode();
	~UGadgetMountingNode();

	///<summary>Returns the pointer to the mounted gadget, can be nullptr</summary>
	///<returns>Pointer to mounted gadget</returns>
	AGadget* GetMountedGadget();

	///<summary>Sets the internal refrence for the mounted gadget</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted gadget</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedGadget(AGadget* toSetTo);

	///<summary>Returns the pointer to the mounted Pawn, can be nullptr</summary>
	///<returns>Pointer to mounted Pawn</returns>
	AMountablePawn* GetMountedPawn();

	///<summary>Sets the internal refrence for the mounted Pawn</summary>
	///<params name='toSetTo'>Pointer to replace current refrence to mounted Pawn</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedPawn(AMountablePawn* toSetTo);
};
