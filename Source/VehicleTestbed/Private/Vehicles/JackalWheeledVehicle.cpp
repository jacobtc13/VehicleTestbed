// Fill out your copyright notice in the Description page of Project Settings.

#include "JackalWheeledVehicle.h"
#include "Engine/SkeletalMeshSocket.h"
#include "ConstructorHelpers.h"

AJackalWheeledVehicle::AJackalWheeledVehicle(const class FObjectInitializer& PCIP)
{
	PrimaryActorTick.bCanEverTick = true;

	//PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	/*ConstructorHelpers::FObjectFinder<USkeletalMesh> JackalAsset(TEXT("SkeletalMesh'/Game/Vehicle/Countermeasures/JackalProjectileCM.JackalProjectileCM'")); 
	if (JackalAsset.Succeeded())
	{
		Mesh = JackalAsset.Object;
		
		RootComponent = Cast<USceneComponent>(Mesh);
		//JackalStaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		//JackalStaticMeshComponent->SetWorldScale3D(FVector(1.f));
	}*/

	/*JackalMesh = GetMesh();
	const USkeletalMeshSocket* Sock = JackalMesh->GetSocketByName(FName(TEXT("JackalShield")));
	if (Sock != nullptr)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> JackalAsset(TEXT("SkeletalMesh'/Game/Vehicle/Countermeasures/JackalProjectileCM.JackalProjectileCM'"));
		m_cUClassWeapon = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("Class'/Script/VehicleTestbed.Gadget'"));
	}*/

	// Setup Jackal specific camera distances
	ChaseCamera->RelativeLocation = FVector(-300.0f, 15.0f, 50.0f);
	CameraSpringArm->RelativeRotation = FRotator(-15.f, 0.f, 0.f);
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	InternalCamera->RelativeLocation = FVector(41.0, 0.0f, 65.0f);

	OverheadCamera->RelativeLocation = FVector(0.f, 0.f, 1000.f);
	OverheadCamera->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	/*Gadget = NewObject<AGadget>(AGadget::StaticClass());
	if (Gadget != nullptr)
	{
		Gadget->AttachComponent(this, FName(TEXT("JackalShield")));
	}*/
}

AJackalWheeledVehicle::~AJackalWheeledVehicle()
{
}

void AJackalWheeledVehicle::BeginPlay()
{
	Super::BeginPlay();

	//JackalStaticMeshComponent = CreateDefaultSubobject<AGadget>(TEXT("Jackal Mesh"));  //ConstructorHelpers::FObjectFinder<UStaticMeshComponent>MeshRef(TEXT("Game/ThirdPerson/Meshes/CubeMesh.CubeMesh"));
	//const ConstructorHelpers::FObjectFinder<Blueprint> GadgetObj(TEXT("Blueprint'/Game/Vehicle/Countermeasures/JackalProjectileCM_BP.JackalProjectileCM_BP'"));
	//auto Gadgeta = GadgetObj.Object;
	//JackalStaticMeshComponent->SetStaticMesh(MeshObj.Object);
	/*if (Gadget != nullptr)
	{
		Gadget->AttachComponent(this, FName(TEXT("JackalShield")));
	}*/
}

void AJackalWheeledVehicle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttachGadget();
}

void AJackalWheeledVehicle::AttachGadget()
{
	//static ConstructorHelpers::FClassFinder<AShieldCountermeasure> ShieldCountermeasure(TEXT("Class'/Script/VehicleTestbed.ShieldCountermeasure'"));
	//if (ShieldCountermeasure.Succeeded())
	//{
		//Gadget = ShieldCountermeasure.Class;
		//Gadget->AttachToComponent(Cast<USceneComponent>(GetMesh()->SkeletalMesh), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, TEXT("ShieldSocket")));
	//}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Gadget = this->GetWorld()->SpawnActor<AShieldCountermeasure>(AShieldCountermeasure::StaticClass(), FVector(93331.0, 182430.0, -49644.0), FRotator::ZeroRotator, SpawnInfo);
	//Gadget = NewObject<AShieldCountermeasure>(AShieldCountermeasure::StaticClass());
	if (Gadget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached"));
		Gadget->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ShieldSocket"));
	}
}


