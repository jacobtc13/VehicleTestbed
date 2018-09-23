// Fill out your copyright notice in the Description page of Project Settings.

#include "Gadget.h"

AGadget::AGadget()
{
	PrimaryActorTick.bCanEverTick = true;
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
	
}