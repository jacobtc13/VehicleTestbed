// Fill out your copyright notice in the Description page of Project Settings.

#include "MountablePawn.h"


// Sets default values
AMountablePawn::AMountablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<UGadgetMountingNode*>* AMountablePawn::GetMountingNodes()
{
	return nullptr;
}

// Called when the game starts or when spawned
void AMountablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMountablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMountablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMountablePawn::MountGadget(AGadget* toAdd, FName filter)
{
	TArray<UGadgetMountingNode*> nodes = *(GetMountingNodes());//passed through as a pointer, defrerenced so now nodes is just a normal variable referring to the correct object in memory

	int i = 0;
	while (i < nodes.Num())
	{
		if (nodes[i]->GetRelatedSocketName() == filter)
		{
			nodes[i]->SetMountedGadget(toAdd);
		}

		i += 1;
	}
}

void AMountablePawn::DismountGadget(AGadget toDismount)
{
	TArray<UGadgetMountingNode*> nodes = *(GetMountingNodes());//passed through as a pointer, defrerenced so now nodes is just a normal variable referring to the correct object in memory

	int i = 0;
	while (i < nodes.Num())
	{
		if (*(nodes[i]->GetMountedGadget()) == toDismount)
		{
			nodes[i]->ClearMountedGadget();
		}

		i += 1;
	}
}

