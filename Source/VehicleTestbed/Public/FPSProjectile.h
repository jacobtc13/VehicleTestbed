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

	UFUNCTION()
	///<summary>Called when the projectile overlaps another object in game</summary>
	///<param name='OverlappedComp'>A pointer to the primitive component that was overlapped</param> 
	///<param name='OtherActor'>A pointer to the actor that was overlapped</param> 
	///<param name='OtherComp'>A pointer to the other primitive component that was overlapped</param> 
	///<param name='OtherBodyIndex'>The index of the other body</param> 
	///<param name='bFromSweep'>Was overlap detected during sweep</param> 
	///<param name='SweepResult'>A reference to the result of the sweep</param> 
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

