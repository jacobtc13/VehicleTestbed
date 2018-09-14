// Fill out your copyright notice in the Description page of Project Settings.

#include "MountablePawn.h"
#include "ConstructorHelpers.h"


// Sets default values
AMountablePawn::AMountablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AMountablePawn::~AMountablePawn()
{

}

TArray<UGadgetMountingNode*> AMountablePawn::GetMountingNodes()
{
	return _mountingNodes;
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

void AMountablePawn::MountGadget(AGadget* toAdd, FName socketName)
{
	for(int i = 0; i < _mountingNodes.Num(); i++)
	{
		if (_mountingNodes[i]->GetRelatedSocketName() == socketName)
		{
			_mountingNodes[i]->SetMountedGadget(toAdd);
			break;
		}
	}
}

void AMountablePawn::DismountGadget(AGadget* toDismount)
{
	for(int i = 0; i < _mountingNodes.Num(); i++)
	{
		if (_mountingNodes[i]->GetMountedGadget() == toDismount)
		{
			_mountingNodes[i]->ClearMountedGadget();
		}
	}
}

