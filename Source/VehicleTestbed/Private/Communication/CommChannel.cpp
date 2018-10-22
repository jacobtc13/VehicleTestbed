#include "CommChannel.h"

UCommChannel::UCommChannel() : UObject()
{}

UCommChannel::UCommChannel(float aFrequency, ISNRModel* aModel) : UObject()
{
	Frequency = aFrequency;
	SNRModel = aModel;
}

//Adds a reciever to the channel
void UCommChannel::AddReceivers(TArray<IMessageReceiver*>& Input)
{
	for (const auto& var : Input)
	{
		ReceiverList.AddUnique(var);
	}
}

void UCommChannel::RemoveReceivers(TArray<IMessageReceiver*>& Input)
{
	for (const auto& var : Input)
	{
		ReceiverList.Remove(var);
	}
}

//Gives each receiver in the channel the message.
//TODO: Make a method that distributes message to the receivers
void UCommChannel::Broadcast(const IMessage& message) const
{
	//Check if there are receivers in the list
	if (GetReceivers().Num() > 0)
	{
		for (const auto& Receiver : GetReceivers())
		{
			//Pass message to receiver here
		}
	}
	else
	{
		//Log event - message was not broadcast to any receiver.
	}
}

//Getters

float UCommChannel::GetFrequency() const
{
	return UCommChannel::Frequency;
}

TArray<IMessageReceiver*> UCommChannel::GetReceivers() const
{
	return ReceiverList;
}
