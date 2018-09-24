// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalWheeledVehicle.h"
#include "ShieldCountermeasure.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h"
#include "ConstructorHelpers.h"

AJackalWheeledVehicle::AJackalWheeledVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up the root scene component for the pawn
	JackalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootComponent"));
	RootComponent = JackalMesh;
	JackalMesh->SetCollisionProfileName(TEXT("Pawn"));

	// Find and initialise the SkeletalMesh as the main mesh for the object
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'"));
	if (SkeletalMesh.Succeeded())
	{
		JackalMesh->SetSkeletalMesh(SkeletalMesh.Object);

		// Set the physics collision mesh to the current skeletal mesh
		static ConstructorHelpers::FObjectFinder<UPhysicsAsset> PhysicsMesh(TEXT("PhysicsAsset'/Game/Vehicle/Jackal/Jackal_PhysicsAsset.Jackal_PhysicsAsset'"));
		if (PhysicsMesh.Succeeded())
		{
			JackalMesh->SetPhysicsAsset(PhysicsMesh.Object);
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

	// Setup Jackal specific camera distances
	ChaseCamera->RelativeLocation = FVector(-300.0f, 15.0f, 50.0f);
	CameraSpringArm->RelativeRotation = FRotator(-15.f, 0.f, 0.f);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	InternalCamera->RelativeLocation = FVector(41.0, 0.0f, 65.0f);

	OverheadCamera->RelativeLocation = FVector(0.f, 0.f, 1000.f);
	OverheadCamera->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	
}

AJackalWheeledVehicle::~AJackalWheeledVehicle()
{
}

void AJackalWheeledVehicle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Initialises default socket names
	if (JackalMesh->SkeletalMesh != nullptr)
	{
		const TArray<USkeletalMeshSocket*> AllSockets = GetMesh()->SkeletalMesh->GetActiveSocketList();
		// TODO: use skeletalmeshsocket instead of name

		// For each socket, create a GadgetMountingNode
		for (int i = 0; i < AllSockets.Num(); i++)
		{
			UGadgetMountingNode* MountingNode = NewObject<UGadgetMountingNode>(UGadgetMountingNode::StaticClass());
			MountingNode->SetMeshSocket(AllSockets[i]);
			GadgetMountingNodes.Add(MountingNode);
		}
	}
	AttachGadget(AShieldCountermeasure::StaticClass(), GadgetMountingNodes[0]->GetMeshSocket());
}

void AJackalWheeledVehicle::AttachGadget(TSubclassOf<AGadget> GadgetClass, USkeletalMeshSocket* Socket)
{
	UE_LOG(LogTemp, Warning, TEXT("Start loop"));
	for (int i = 0; i < GadgetMountingNodes.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Loop"));
		if (Socket == GadgetMountingNodes[i]->GetMeshSocket())
		{
			UE_LOG(LogTemp, Warning, TEXT("Succ"));
			if (1)//GadgetMountingNodes[i]->SetMountedGadget(GadgetClass, this) != nullptr) // change
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AGadget* Gadget = this->GetWorld()->SpawnActor<AGadget>(GadgetClass.Get(), FVector(93331.0, 182430.0, -49644.0), FRotator::ZeroRotator, SpawnInfo); // Change FVector
				if (Gadget == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Error initialising countermeasure class."));
				}
				// Attach gadget to the vehicle
				Gadget->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ShieldSocket")); // Fix
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error initialising countermeasure class."));
			}
		}
	}

	//FActorSpawnParameters SpawnInfo;
	//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// TODO: change the FVector
	//Gadget = this->GetWorld()->SpawnActor<AShieldCountermeasure>(AShieldCountermeasure::StaticClass(), FVector(93331.0, 182430.0, -49644.0), FRotator::ZeroRotator, SpawnInfo);
	//if (Gadget != nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Reached"));
	//	Gadget->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ShieldSocket"));
	//}
}


