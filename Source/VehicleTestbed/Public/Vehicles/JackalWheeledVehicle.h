// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicles/TestbedWheeledVehicle.h"

#include "Gadget.h"
#include "GadgetMountingNode.h"

#include "JackalWheeledVehicle.generated.h"

UCLASS()
///<summary>Class to represent the Clearpath Jackal.</summary>
class VEHICLETESTBED_API AJackalWheeledVehicle : public ATestbedWheeledVehicle
{
	GENERATED_BODY()

public:
	AJackalWheeledVehicle();

	~AJackalWheeledVehicle();

	void AttachGadget(TSubclassOf<AGadget> GadgetClass, FName SocketName);

	void PostInitializeComponents();

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* JackalMesh;

	UPROPERTY(EditAnywhere, Category = "Gadget")
	AGadget* Gadget;

	UPROPERTY(EditAnywhere, Category = "Gadget")
	TArray<FName> SocketNames = {};

	UPROPERTY(EditAnywhere, Category = "Gadget")
	TArray<UGadgetMountingNode*> GadgetMountingNodes;
};
