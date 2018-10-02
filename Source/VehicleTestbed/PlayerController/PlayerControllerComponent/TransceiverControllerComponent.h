#pragma once

#include "Communication/Message.h"

#include "CoreMinimal.h"
#include "PlayerController/PlayerControllerComponent/PCComponent.h"
#include "TransceiverControllerComponent.generated.h"

UCLASS()
class VEHICLETESTBED_API UTransceiverControllerComponent : public UPCComponent
{
	GENERATED_BODY()

public:
	///<summary></summary>
	///<param name="InputComponent">The input component of the TestbedPlayerController</param>
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	///<summary>Interprets the message</summary>
	///<param name="Message">The message to interpret</param>
	virtual void InterpretMessage(const IMessage& Message);
};
