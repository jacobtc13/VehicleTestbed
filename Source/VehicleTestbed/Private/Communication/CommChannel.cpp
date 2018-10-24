#include "CommChannel.h"

UCommChannel::UCommChannel() : UObject()
{}

UCommChannel::UCommChannel(float aFrequency, USNRModel* aModel) : UCommChannel()
{
	Initialize(aFrequency, aModel);
}

void UCommChannel::Initialize(float aFrequency, USNRModel * aModel)
{
	Frequency = aFrequency;
	SNRModel = aModel;
}

//Adds a reciever to the channel
void UCommChannel::AddReceivers(const TArray<UObject*>& Receivers)
{
	for (const auto& Receiver : Receivers)
	{
		if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
		{
			ReceiverList.AddUnique(Receiver);
		}
	}
}

void UCommChannel::RemoveReceivers(const TArray<UObject*>& Receivers)
{
	for (const auto& Receiver : Receivers)
	{
		if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
		{
			ReceiverList.Remove(Receiver);
		}
	}
}

//Gives each receiver in the channel the message.
//TODO: Make a method that distributes message to the receivers
void UCommChannel::Broadcast(const IMessage& message, const FVector SenderPos) const
{
	//Check if there are receivers in the list
	if (GetReceivers().Num() > 0)
	{
		for (const auto& Receiver : GetReceivers())
		{
			//Pass message to receiver here
			if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
			{
				MessageReceiver->Receive(message, SNRModel->CalculateSNR(SenderPos, MessageReceiver->GetLocation()));
			}
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

TArray<UObject*> UCommChannel::GetReceivers() const
{
	return ReceiverList;
}
