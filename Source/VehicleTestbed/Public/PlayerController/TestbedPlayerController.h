#pragma once

#include "PauseMenuComponent.h"
#include "PawnSwapComponent.h"
#include "JackalControlComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestbedPlayerController.generated.h"

UCLASS()
class VEHICLETESTBED_API ATestbedPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATestbedPlayerController();

	///<summary>Allows the PlayerController to set up custom input bindings</summary>
	virtual void SetupInputComponent() override;

	///<summary>Event that is called when play begins for this actor</summary>
	virtual void BeginPlay() override;

	// Components
protected:
	UPauseMenuComponent* PauseMenuComponent;
	UPawnSwapComponent* PawnSwapComponent;
	UJackalControlComponent* JackalControlComponent;
};
