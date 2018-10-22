#pragma once

#include "GameFramework/PlayerController.h"
#include "EventRecorder/EventRecorder.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PCComponent.generated.h"

UCLASS(Abstract)
class VEHICLETESTBED_API UPCComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	///<summary>Default constructor.  Gets a reference to the TestbedPlayerController it is a component of.</summary>
	UPCComponent()
		: UActorComponent()
	{
		Controller = (APlayerController*)GetOwner();
	}

	///<summary>Needs to be overriden in sub classes.  Put input bindings in here and call this function in the SetupPlayerInputComponent() function of the TestbedPlayerController</summary>
	///<param name="inputComponent">The input component of the TestbedPlayerController</param>
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent)
	{
		check(0 && "You must override this");
	}

	///<summary>Called automatically by Unreal, override this if you need to.</summary>
	virtual void BeginPlay() override
	{
		UActorComponent::BeginPlay();
	}

protected:
	APlayerController* Controller;
};
