#pragma once

#include "TransceiverControllerComponent.h"
#include "CoreMinimal.h"
#include "DemoTransceiverControllerComponent.generated.h"

UCLASS()
class UDemoTransceiverControllerComponent : public UTransceiverControllerComponent
{
	GENERATED_BODY()

public:
	///<summary></summary>
	///<param name="InputComponent">The input component of the TestbedPlayerController</param>
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	///<summary>Interprets the message</summary>
	///<param name="Message">The message to interpret</param>
	virtual void InterpretMessage(const UMessage* Message) override;
};
