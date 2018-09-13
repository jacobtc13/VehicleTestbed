// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMountingNode.h"
#include "Gadget.generated.h"

/**
 * Base class for mounting/dismounting to an AMountablePAwn
 */
UCLASS()
class VEHICLETESTBED_API AGadget : public AActor
{
	GENERATED_BODY()

public:
	AGadget();
	~AGadget();

	UFUNCTION()
	///<summary>Returns true if this Gadget is mounted, otherwise false</summary>
	bool IsMounted();

	UFUNCTION()
	///<summary>Returns a pointer to the currently mounted pawn, can be NULL</summary>
	///<returns>A pointer to the currently mounted Pawn</returns>
	UGadgetMountingNode* GetMountedMountingNode();

	UFUNCTION()
	///<summary>Sets the internal reference for the currently mounted pawn</summary>
	///<params name ='toSetTo'>Address of the Pawn this Gadget is mounted to</params>
	///<returns>Error code, 0 success, 1 success overriding data</returns>
	int SetMountedMountingNode(UGadgetMountingNode* toSetTo);

private:
	///<summary>The internal reference for the currently mounted pawn</summary>
	UGadgetMountingNode* _mountedMountingNode = nullptr;

};
