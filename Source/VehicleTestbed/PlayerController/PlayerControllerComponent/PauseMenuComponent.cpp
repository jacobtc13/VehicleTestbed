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

void UPauseMenuComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("PauseButton", IE_Released, this, &UPauseMenuComponent::Pause);
}

void UPauseMenuComponent::BeginPlay()
{
	UPCComponent::BeginPlay();

	pauseMenu = CreateWidget<UUserWidget>(Controller, pauseMenuClass);
}

void UPauseMenuComponent::Pause()
{
	pauseMenu->AddToViewport();
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->bShowMouseCursor = true;
	Controller->SetPause(true);
}