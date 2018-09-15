#pragma once

#include "UserWidget.h"
#include "ConstructorHelpers.h"

#include "PlayerController/PlayerControllerComponent/PCComponent.h"
#include "PauseMenuComponent.generated.h"

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class VEHICLETESTBED_API UPauseMenuComponent : public UPCComponent
{
	GENERATED_BODY()

public:
	///<summary>Default constructor.  Gets a reference to the class of the pause widget so it can be instantiated later</summary>
	UPauseMenuComponent();

	///<summary>Needs to be overriden in sub classes.  Put input bindings in here and call this function in the SetupPlayerInputComponent() function of the TestbedPlayerController</summary>
	///<param name="inputComponent">The input component of the TestbedPlayerController</param>
	void SetupPlayerInputComponent(UInputComponent* inputComponent) override;

	///<summary>Called automatically by Unreal.  Instantiates an object of the pause menu.</summary>
	void BeginPlay() override;

private:
	TSubclassOf<UUserWidget> pauseMenuClass;
	UUserWidget* pauseMenu;

	///<summary>Adds the pause menu to the screen and pauses the game</summary>
	void Pause();
};