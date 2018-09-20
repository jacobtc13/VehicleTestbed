// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileCountermeasure.h"

AProjectileCountermeasure::AProjectileCountermeasure()
{
	if (bHasMesh)
	{
		InitialiseMesh();
	}
}

AProjectileCountermeasure::~AProjectileCountermeasure()
{

}

void AProjectileCountermeasure::AttachComponent(ATestbedWheeledVehicle* Vehicle, FName SocketName)
{

}

void AProjectileCountermeasure::Activate()
{

}