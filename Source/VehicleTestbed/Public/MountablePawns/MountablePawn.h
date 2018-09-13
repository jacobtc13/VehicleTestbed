// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.h"
#include "GameFramework/Pawn.h"
#include "GadgetMountingNode.h"
#include "MountablePawn.generated.h"

/*
* This class derives from APawn and includes the functionality for mounting/dismounting an AGadet via a dynamic array of UGadgetMouningNodes
*/
UCLASS()
class VEHICLETESTBED_API AMountablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMountablePawn();

	///<summary>Get a pointer to the internal list of UGadgetMouningNode pointers</summary>
	///<returns>A pointer to the dynamic array of pointers to mounting nodes</returns>
	TArray<UGadgetMountingNode*>* GetMountingNodes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	///<summary>Dynamic array of UGadgetMountingNode pointers, holds all of the locations a Gadget can be mounted on the Pawn</summary>
	TArray<UGadgetMountingNode*> _mountingNodes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///<summary>Adds the AGadget toAdd to all UGadgetMountingNodes related to the socket denoted by FName toAddTo</summary>
	///<params name = 'toAdd'>Pointer to AGadget to add to desired UGadgetNodes</params>
	///<params name = 'filter'>FName to filter for when selecting which UGadgetMountingNodes to add toAdd to</params>
	void MountGadget(AGadget* toAdd, FName filter);

	///<summary>Removes the AGadget toDismount from all UGadgetMountingNodes in _mountingNodes</summary>
	///<params name = 'toDismount'>The AGadget to be dismounted</params>
	void DismountGadget(AGadget toDismount);
};
