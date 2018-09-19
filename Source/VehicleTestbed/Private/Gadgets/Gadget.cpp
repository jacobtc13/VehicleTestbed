// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"
#include "ConstructorHelpers.h"

AGadget::AGadget(const class FObjectInitializer& PCIP)
{
	PrimaryActorTick.bCanEverTick = true;

	//ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshRef(TEXT("SkeletalMesh'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'"));
	GadgetMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Vehicle/Jackal/Jackal_Mesh.Jackal_Mesh'"));

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