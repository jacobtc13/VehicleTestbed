#include "DemoTransceiverControllerComponent.h"
#include "DemoMessage.h"
#include "Engine.h"

void UDemoTransceiverControllerComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{

}

void UDemoTransceiverControllerComponent::InterpretMessage(const UMessage* Message)
{
	if (const UDemoMessage* DemoMessage = Cast<const UDemoMessage>(Message))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Received Message"));
	}
}
