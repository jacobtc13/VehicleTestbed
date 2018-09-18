// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gadget.h"
#include "GameFramework/Character.h"
#include "GadgetMountingNode.h"
#include "Engine/SkeletalMesh.h"
#include "MountablePawn.generated.h"

/*
* This class derives from APawn and includes the functionality for mounting/dismounting an AGadet via a dynamic array of UGadgetMouningNodes
*/
UCLASS()
class VEHICLETESTBED_API AMountablePawn : public APawn
{
	GENERATED_BODY()

public:
	AMountablePawn();

	~AMountablePawn();

	///<summary>Get a pointer to the internal list of UGadgetMouningNode pointers</summary>
	///<returns>A pointer to the dynamic array of pointers to mounting nodes</returns>
	TArray<UGadgetMountingNode*> GetMountingNodes();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///<summary>Adds the AGadget toAdd to all UGadgetMountingNodes related to the socket denoted by FName toAddTo</summary>
	///<params name = 'toAdd'>Pointer to AGadget to add to desired UGadgetNodes</params>
	///<params name = 'socketName'>FName to select socket that will have gadget removed from</params>
	void MountGadget(AGadget* toAdd, FName socketName);

	///<summary>Removes the AGadget toDismount from all UGadgetMountingNodes in _mountingNodes</summary>
	///<params name = 'toDismount'>The AGadget to be dismounted</params>
	///<params name = 'socketName'>FName to select socket that will have gadget removed from</params>
	void DismountGadget(FName socketName);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	TArray<FName> socketNames;

private:
	UPROPERTY()
	///<summary>Dynamic array of UGadgetMountingNode pointers, holds all of the locations a Gadget can be mounted on the Pawn</summary>
	TArray<UGadgetMountingNode*> mountingNodes;
};
