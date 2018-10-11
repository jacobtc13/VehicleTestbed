// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"


class UProjectileMovementComponent;
class USphereComponent;


UCLASS()
class AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	///<summary>Constructor for the AFPSProjectile class</summary>
	AFPSProjectile();

	///<summary>Gets the collision component of the projectile</summary>
	///<returns>A pointer to the CollisionComp</returns>  
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	///<summary>Gets the projectile movement of the projectile</summary>
	///<returns>A pointer to the ProjectileMovement</returns>  
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Projectile")
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;
};

