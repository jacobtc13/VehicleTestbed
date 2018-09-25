// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileCountermeasure.h"

#include "Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h"

#include "ConstructorHelpers.h"

AProjectileCountermeasure::AProjectileCountermeasure()
{
	PrimaryActorTick.bCanEverTick = true;
	InitialiseMesh();
}

AProjectileCountermeasure::~AProjectileCountermeasure()
{

}

void AProjectileCountermeasure::InitialiseMesh()
{
	// Set up the root scene component for the pawn
	USkeletalMeshComponent* MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Find and initialise the SkeletalMesh as the main mesh for the object
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(MeshLocation);
	if (SkeletalMesh.Succeeded())
	{
		MeshComponent->SetSkeletalMesh(SkeletalMesh.Object);

		// Set the physics collision mesh to the current skeletal mesh
		static ConstructorHelpers::FObjectFinder<UPhysicsAsset> PhysicsMesh(PhysicsAssetLocation);
		if (PhysicsMesh.Succeeded())
		{
			MeshComponent->SetPhysicsAsset(PhysicsMesh.Object);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("The Gadget PhysicsAsset cannot be found. Please update the location in the C++ source if it has been moved."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Gadget SkeletalMesh asset cannot be found. Please update the location in the C++ source if it has been moved."));
	}

	SetActorEnableCollision(true);
}

void AProjectileCountermeasure::Activate()
{
	// TODO: Implement firing method
}