#include "PauseMenuComponent.h"

UPauseMenuComponent::UPauseMenuComponent()
	: UPCComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> pauseMenuFinder(TEXT("/Game/HUDs/Menus/MenuWidgets/PauseMenuWidget"));
	// This throws a warning when loading the editor if it can't find it so no need to handle that case
	if (pauseMenuFinder.Succeeded())
	{
		pauseMenuClass = pauseMenuFinder.Class;
	}
}

void UPauseMenuComponent::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	check(inputComponent);
	inputComponent->BindAction("PauseButton", IE_Released, this, &UPauseMenuComponent::Pause);
}

void UPauseMenuComponent::BeginPlay()
{
	UActorComponent::BeginPlay();

	pauseMenu = CreateWidget<UUserWidget>(controller, pauseMenuClass);
}

void UPauseMenuComponent::Pause()
{
	pauseMenu->AddToViewport();
	controller->SetInputMode(FInputModeUIOnly());
	controller->bShowMouseCursor = true;
	controller->SetPause(true);
}