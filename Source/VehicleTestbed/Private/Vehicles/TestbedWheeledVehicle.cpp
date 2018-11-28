#include "TestbedWheeledVehicle.h"

#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

#include "ProjectileCountermeasure.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h"

#include "WheeledVehicleMovementComponent.h"
#include "CoreMinimal.h"

ATestbedWheeledVehicle::ATestbedWheeledVehicle()
{
	Transceiver = CreateDefaultSubobject<UPerfectTransceiver>(TEXT("Transceiver"));
	Transceiver->Initialize(100, 20, 1, 0);

	// All camera position values need to be manually changed based on size of vehicle in inherited classes.
	// Use a spring arm to give the camera smooth, natural-feeling motion.
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);

	// Create a camera and attach to our spring arm
	ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	ChaseCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	// Create internal camera for viewing from inside vehicle
	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	InternalCamera->SetupAttachment(RootComponent);

	// Create overhead camera for viewing from above the vehicle
	OverheadCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OverheadCamera"));
	OverheadCamera->SetupAttachment(RootComponent);

	ActiveCamera = ChaseCamera;
	ActiveCamera->Activate();
}

ATestbedWheeledVehicle::~ATestbedWheeledVehicle()
{

}

void ATestbedWheeledVehicle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Initialises default socket names
	if (GetMesh()->SkeletalMesh != nullptr)
	{
		// Get all sockets on the mesh
		const TArray<USkeletalMeshSocket*> AllSockets = GetMesh()->SkeletalMesh->GetActiveSocketList();

		// For each socket, create a GadgetMountingNode
		for (int i = 0; i < AllSockets.Num(); i++)
		{
			UGadgetMountingNode* MountingNode = NewObject<UGadgetMountingNode>(UGadgetMountingNode::StaticClass());
			MountingNode->SetMeshSocket(AllSockets[i]);
			GadgetMountingNodes.Add(MountingNode);
		}
	}
}

void ATestbedWheeledVehicle::SetThrottleInput(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void ATestbedWheeledVehicle::SetSteeringInput(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void ATestbedWheeledVehicle::SetBrakeInput(float Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value);
}

float ATestbedWheeledVehicle::GetVehicleForwardSpeed() const
{
	// Conversion is done to output result in km/h
	return GetVehicleMovementComponent()->GetForwardSpeed() * 0.036f;
}

void ATestbedWheeledVehicle::SwitchToOverheadCamera()
{
	SwitchActiveCamera(OverheadCamera);
}

void ATestbedWheeledVehicle::SwitchToInternalCamera()
{
	SwitchActiveCamera(InternalCamera);
}

void ATestbedWheeledVehicle::SwitchToChaseCamera()
{
	SwitchActiveCamera(ChaseCamera);
}

void ATestbedWheeledVehicle::SwitchActiveCamera(UCameraComponent* NewActiveCamera)
{
	ActiveCamera->Deactivate();
	ActiveCamera = NewActiveCamera;
	ActiveCamera->Activate();
}

TArray<UGadgetMountingNode*> ATestbedWheeledVehicle::GetMountingNodes()
{
	return GadgetMountingNodes;
}

UGadgetMountingNode* ATestbedWheeledVehicle::GetMountingNodeBySocketName(FName SocketName)
{
	for (int i = 0; i < GadgetMountingNodes.Num(); i++)
	{
		if (SocketName == GadgetMountingNodes[i]->GetMeshSocket()->SocketName)
		{
			return GadgetMountingNodes[i];
		}
	}

	// Return nullptr if nothing is found with that name
	return nullptr;
}

void ATestbedWheeledVehicle::MountGadget(TSubclassOf<AGadget> GadgetClass, USkeletalMeshSocket* Socket)
{
	for (int i = 0; i < GadgetMountingNodes.Num(); i++)
	{
		if (Socket == GadgetMountingNodes[i]->GetMeshSocket())
		{
			// Make object capable of spawning anywhere, because it will be attached to socket anyway
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AGadget* Gadget = this->GetWorld()->SpawnActor<AGadget>(GadgetClass.Get(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

			// Check if gadget was successfully created
			if (Gadget != nullptr)
			{
				// Attach to mounting node
				GadgetMountingNodes[i]->SetMountedGadget(Gadget);

				// Attach gadget mesh to the vehicle
				Gadget->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket->SocketName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error initialising countermeasure class."));
			}
		}
	}
}