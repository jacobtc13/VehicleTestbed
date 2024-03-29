#include "CommChannel.h"

UCommChannel::UCommChannel() : UObject()
{}

void UCommChannel::Initialize(float aFrequency, USNRModel* aModel)
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
void UCommChannel::Broadcast(const UMessage* Message, const float SignalPower, const FVector SenderPos) const
{
	//Check if there are receivers in the list
	if (GetReceivers().Num() > 0)
	{
		for (const auto& Receiver : GetReceivers())
		{
			//Pass message to receiver here
			if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
			{
				MessageReceiver->Receive(Message, SNRModel->CalculateSNR(SignalPower, SenderPos, MessageReceiver->GetLocation()));
			}
		}
	}
	else
	{
		//Log event - message was not broadcast to any receiver.
		UEventRecorder::RecordEvent(TEXT("Message not broadcast to any receiver"), this);
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

USNRModel* UCommChannel::GetSNRModel() const
{
	return SNRModel;
}

void UCommChannel::SetSNRModel(USNRModel* NewSNRModel)
{
	SNRModel = NewSNRModel;
}
