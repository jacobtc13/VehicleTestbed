// Fill out your copyright notice in the Description page of Project Settings.

#include "MountablePawn.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMeshSocket.h"
#include "ConstructorHelpers.h"


AMountablePawn::AMountablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (int i = 0; i < socketNames.Num(); i++)
	{
		UGadgetMountingNode* newNode = NewObject<UGadgetMountingNode>(UGadgetMountingNode::StaticClass());
		mountingNodes.Add(newNode);
	}

	// TODO: Second loop that adds the gadget to the nodes based on spawn logic
	
	/*auto *mesh = GetMesh();
	const USkeletalMeshSocket* weaponSocket;
	weaponSocket = GetMesh()->GetSocketByName(FName("WeaponSocket"));
	FName fnWeaponSocket = weaponSocket->GetFName();

	FName fnWeaponSocket = TEXT("WeaponSocket");
	m_cUClassWeapon = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Blueprints/CharacterController/BP_Pistol.BP_Pistol_C"));
	m_cWeapon = GetWorld()->SpawnActor<AWeapon>(m_cUClassWeapon, spawnParams);
	m_cWeapon->AttachRootComponentTo(GetMesh(), fnWeaponSocket, EAttachLocation::SnapToTarget, true);*/
}

AMountablePawn::~AMountablePawn()
{

}

void AMountablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMountablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<UGadgetMountingNode*> AMountablePawn::GetMountingNodes()
{
	return mountingNodes;
}

void AMountablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMountablePawn::MountGadget(AGadget* toAdd, FName socketName)
{
	for(int i = 0; i < mountingNodes.Num(); i++)
	{
		if (mountingNodes[i]->GetRelatedSocketName() == socketName)
		{
			mountingNodes[i]->SetMountedGadget(toAdd);
		}
	}
}

void AMountablePawn::DismountGadget(FName socketName)
{
	for(int i = 0; i < mountingNodes.Num(); i++)
	{
		if (mountingNodes[i]->GetRelatedSocketName() == socketName)
		{
			mountingNodes[i]->RemoveMountedGadget();
		}
	}
}

