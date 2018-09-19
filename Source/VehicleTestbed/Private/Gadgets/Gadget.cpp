// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"
#include "ConstructorHelpers.h"

AGadget::AGadget(const class FObjectInitializer& PCIP)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Cast<USceneComponent>(Mesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMeshComponent>MeshRef(TEXT("SkeletalMeshComponent'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'"));
	Mesh = MeshRef.Object;
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