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

