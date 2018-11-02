#include "TransceiverControllerComponent.h"
#include "MessageTemplate.h"
#include "MessageReceiver.h"

void UTransceiverControllerComponent::SetupPlayerInputComponent(UInputComponent* InputComponent)
{

}


void UTransceiverControllerComponent::InterpretMessage(const UMessage* Message)
{
	typedef IMessageReceiver::EResponseCode EResponseCode;
	if (const TMessageTemplate<EResponseCode>* ResponseMessage = Cast<const TMessageTemplate<EResponseCode>>(Message))
	{
		EResponseCode ResponseCode = ResponseMessage->Get();
		switch (ResponseCode)
		{
		case EResponseCode::Garbled:
		{
			// Logic of attempting to resend the message would go here
			// In this example transceiver the message is not resent
			break;
		}
		case EResponseCode::Received:
		{
			// Logic of what to do when the receiver confirms they have received the message
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		// Doesn't understand the message
		// Assume it is not meant for this unit
	}
}
