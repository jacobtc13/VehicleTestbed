// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GadgetMountingNode.h"
#include "MountablePawn.generated.h"

UCLASS()
class VEHICLETESTBED_API AMountablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMountablePawn();

	///<summary>Get a pointer to the internal list of UGadgetMouningNode pointers</summary>
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

};
