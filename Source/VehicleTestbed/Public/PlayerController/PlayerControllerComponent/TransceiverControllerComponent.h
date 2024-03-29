#pragma once

#include "Message.h"

#include "CoreMinimal.h"
#include "PCComponent.h"
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
	virtual void InterpretMessage(const UMessage* Message);

	enum EResponseCode
	{
		// Used to denote that a message was received successfully
		Received,
		// Used to denote that a message was heard but not clearly enough to interpret
		Garbled
	};
};
