// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "ConstructorHelpers.h"

AGadget::AGadget()
{
	if (bHasMesh)
	{
		InitialiseMesh();
	}
}

AGadget::~AGadget()
{
}

void AGadget::AttachComponent(ATestbedWheeledVehicle* Vehicle, FName SocketName)
{
	AttachToComponent(Cast<USceneComponent>(Vehicle->GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}

void AGadget::Activate()
{

}

void AGadget::InitialiseMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up the root scene component for the pawn
	USkeletalMeshComponent* MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Find and initialise the SkeletalMesh as the main mesh for the object
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(SkeletalMeshLocation);
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
			UE_LOG(LogTemp, Warning, TEXT("The Gadget PhysicsAsset cannot be found. Please update the location in C++ if it has been moved."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Gadget SkeletalMesh asset cannot be found. Please update the location in C++ if it has been moved."));
	}

	SetActorEnableCollision(true);
}