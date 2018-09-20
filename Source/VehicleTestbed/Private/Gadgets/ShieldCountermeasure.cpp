// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldCountermeasure.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "ConstructorHelpers.h"

AShieldCountermeasure::AShieldCountermeasure()
{
	if (bHasMesh)
	{
		InitialiseMesh();
	}
}

AShieldCountermeasure::~AShieldCountermeasure()
{

}

void AShieldCountermeasure::InitialiseMesh()
{
	// Set up the root scene component for the pawn
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Find and initialise the SkeletalMesh as the main mesh for the object
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SkeletalMesh(MeshLocation);
	if (SkeletalMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SkeletalMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Shield StaticMesh asset cannot be found. Please update the location in C++ if it has been moved."));
	}

	SetActorEnableCollision(true);
}

