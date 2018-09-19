// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/TestbedWheeledVehicle.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Gadget.h"
#include "JackalWheeledVehicle.generated.h"

UCLASS()
///<summary>Class to represent the Clearpath Jackal.</summary>
class VEHICLETESTBED_API AJackalWheeledVehicle : public ATestbedWheeledVehicle
{
	GENERATED_BODY()

public:
	AJackalWheeledVehicle(const class FObjectInitializer& PCIP);

	~AJackalWheeledVehicle();

	void BeginPlay();

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* JackalMesh;

	UPROPERTY(EditAnywhere, Category = "Gadget")
	AGadget* Gadget;
};
