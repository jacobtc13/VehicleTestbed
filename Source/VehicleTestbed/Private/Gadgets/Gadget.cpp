// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"

AGadget::AGadget()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> JackalAsset(TEXT("SkeletalMesh'/Game/Vehicle/Countermeasures/JackalProjectileCM.JackalProjectileCM'"));
	if (JackalAsset.Succeeded())
	{
		RootComponent = Cast<USceneComponent>(JackalAsset.Object);
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