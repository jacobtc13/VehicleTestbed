// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalWheeledVehicle.h"
#include "ShieldCountermeasure.h"
#include "Engine/SkeletalMeshSocket.h"

AJackalWheeledVehicle::AJackalWheeledVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Jackal specific camera distances
	ChaseCamera->RelativeLocation = FVector(-300.0f, 15.0f, 50.0f);
	CameraSpringArm->RelativeRotation = FRotator(-15.f, 0.f, 0.f);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	InternalCamera->RelativeLocation = FVector(41.0, 0.0f, 65.0f);

	OverheadCamera->RelativeLocation = FVector(0.f, 0.f, 1000.f);
	OverheadCamera->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	// Initialises default socket names
	SocketNames.Add(TEXT("WeaponSocket"));
	SocketNames.Add(TEXT("ShieldSocket"));
	
	// For each socket, create a GadgetMountingNode
	for (int i = 0; i < SocketNames.Num(); i++)
	{
		UGadgetMountingNode* MountingNode = NewObject<UGadgetMountingNode>(UGadgetMountingNode::StaticClass());
		MountingNode->SetSocketName(SocketNames[i]);
		GadgetMountingNodes.Add(MountingNode);
	}
}

AJackalWheeledVehicle::~AJackalWheeledVehicle()
{
}

void AJackalWheeledVehicle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttachGadget(AShieldCountermeasure::StaticClass(), TEXT("ShieldSocket"));
}

void AJackalWheeledVehicle::AttachGadget(TSubclassOf<AGadget> GadgetClass, FName SocketName)
{
	UE_LOG(LogTemp, Warning, TEXT("Start loop"));
	for (int i = 0; i < GadgetMountingNodes.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Loop"));
		if (SocketName.IsEqual(GadgetMountingNodes[i]->GetSocketName()))
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
				Gadget->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
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


