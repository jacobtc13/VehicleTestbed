#include "CommDistributor.h"
#include "MessageSender.h"

// static initialization
TArray<UCommChannel*> UCommDistributor::ChannelList;
TArray<USNRModelFrequencyRange*> UCommDistributor::PropagateList;
USNRModel* UCommDistributor::DefaultProp = nullptr;

//TODO: Needs to populate the propergateList that the user has defined.

//Sends the message to the designated channel.
void UCommDistributor::Send(const UMessage* Message, UObject* Sender, float SignalPower)
{
	if (IMessageSender* MessageSender = Cast<IMessageSender>(Sender))
	{
		if (CheckForMultiChannels(MessageSender->GetFrequency(), MessageSender->GetVariance()))
		{
			for (const UCommChannel* Channel : GetChannels(MessageSender->GetFrequency(), MessageSender->GetVariance()))
			{
				Channel->Broadcast(Message, SignalPower, MessageSender->GetLocation());
			}
		}
		else
		{
			// Log Event - The channel the sender want to broadcast does not exist.
		}
	}
}

//Adds a IMessageReceiver to a specific channel, Also creates a channel non-existant
void UCommDistributor::AddToChannel(float Frequency, UObject* Receiver)
{
	if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
	{
		CreateChannel(Frequency); // Checks if a channel already exists

		TArray<UCommChannel*> SingleChannelInList = GetChannels(Frequency, 0);
		if (SingleChannelInList.Num())
		{
			UCommChannel* Channel = SingleChannelInList[0];
			//package the input reciever into a TArray of IMessageReceivers
			TArray<UObject*> temp;
			temp.Add(Receiver);
			Channel->AddReceivers(temp);
		}
	}
}

//Removes IMessageReceiver from a specific Channel
void UCommDistributor::RemoveFromChannel(float Frequency, UObject* Receiver)
{
	if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
	{
		TArray<UCommChannel*> SingleChannelInList = GetChannels(Frequency, 0);
		if (SingleChannelInList.Num())
		{
			UCommChannel* Channel = SingleChannelInList[0];
			//package the input receiver into a TArray of UObjects
			TArray<UObject*> temp;
			temp.Add(Receiver);
			Channel->RemoveReceivers(temp);
		}
	}
}

void UCommDistributor::SwitchChannel(float Frequency, UObject* Receiver)
{
	if (IMessageReceiver* MessageReceiver = Cast<IMessageReceiver>(Receiver))
	{
		RemoveFromChannel(MessageReceiver->GetFrequency(), Receiver);
		AddToChannel(Frequency, Receiver);
	}
}

//Checks if a single channel exist
bool UCommDistributor::CheckForChannel(float Frequency)
{
	//Check if there are any channels at all
	if (ChannelList.Num() != 0)
	{
		//Check if the channel exists
		for (const UCommChannel* Channel : ChannelList)
		{
			//Channel exists
			if (Channel->GetFrequency() == Frequency)
			{
				return true;
			}
		}

	}
	//Channel does not exist
	return false;
}

//Returns true if a single channel exists within a range of frequencies
bool UCommDistributor::CheckForMultiChannels(float Frequency, float Variance)
{
	float UpperRange = Frequency + Variance;
	float LowerRange = Frequency - Variance;
	if (ChannelList.Num() != 0)
	{
		for (const UCommChannel* Channel : ChannelList)
		{
			if (Channel->GetFrequency() >= LowerRange && Channel->GetFrequency() <= UpperRange)
			{
				return true;
			}
		}
	}
	return false;
}

//Creates a channel and adds it to the list of channels
void UCommDistributor::CreateChannel(float Frequency)
{
	if (!CheckForChannel(Frequency))
	{
		//Creates a new channel with the associated SNRModel
		UCommChannel* NewChannel = NewObject<UCommChannel>();

		TArray<USNRModelFrequencyRange*> SNRRanges = RetrieveSNRRange(Frequency);
		if (SNRRanges.Num())
		{
			// Use the first SNRModel in the list
			NewChannel->Initialize(Frequency, SNRRanges[0]->GetSNRModel());
		}
		else if (DefaultProp)
		{
			NewChannel->Initialize(Frequency, DefaultProp);
		}
		else
		{
			// Comm Distributor has not been intialized yet
			UE_LOG(LogTemp, Fatal, TEXT("Channel attempted to be made before Distributor is initialized"));
		}

		ChannelList.Add(NewChannel);
	}
}

//Retrieves an array of channels that are in the frequency range
TArray<UCommChannel*> UCommDistributor::GetChannels(float Frequency, float Variance)
{
	TArray<UCommChannel*> Output;
	float UpperRange = Frequency + Variance;
	float LowerRange = Frequency - Variance;
	for (const auto& Channel : ChannelList)
	{
		if (Channel->GetFrequency() >= LowerRange && Channel->GetFrequency() <= UpperRange)
		{
			Output.AddUnique(Channel);
		}
	}
	return Output;
}

//Retrieves the SNR Model Frequency Range from the list
TArray<USNRModelFrequencyRange*> UCommDistributor::RetrieveSNRRange(float Frequency)
{
	TArray<USNRModelFrequencyRange*> Output;
	for (const auto& Range : PropagateList)
	{
		if (Range->GetMaxFrequency() >= Frequency && Range->GetMinFrequency() <= Frequency)
		{
			Output.AddUnique(Range);
		}
	}
	return Output;
}

void UCommDistributor::AddSNRModelForFrequencyRange(USNRModelFrequencyRange* FrequencyRange)
{
	if (FrequencyRange != nullptr)
	{
		PropagateList.Add(FrequencyRange);
		for (UCommChannel* Channel : ChannelList)
		{
			if (Channel->GetSNRModel() == DefaultProp)
			{
				if ((FrequencyRange->GetMinFrequency() <= Channel->GetFrequency()) && (Channel->GetFrequency() <= FrequencyRange->GetMaxFrequency()))
				{
					Channel->SetSNRModel(FrequencyRange->GetSNRModel());
				}
			}
		}
	}
}

void UCommDistributor::RemoveSNRModelFromFrequencyRange(USNRModelFrequencyRange* FrequencyRange)
{
	PropagateList.Remove(FrequencyRange);
	for (UCommChannel* Channel : ChannelList)
	{
		if (Channel->GetSNRModel() == FrequencyRange->GetSNRModel())
		{
			auto RangeList = RetrieveSNRRange(Channel->GetFrequency());
			if (RangeList.Num())
			{
				// Use the first SNRModel in the list
				Channel->SetSNRModel(RangeList[0]->GetSNRModel());
			}
			else
			{
				Channel->SetSNRModel(DefaultProp);
			}
		}
	}
}

USNRModel* UCommDistributor::GetDefaultPropagation()
{
	return DefaultProp;
}

void UCommDistributor::SetDefaultPropagation(USNRModel* NewDefaultProp)
{
	if (NewDefaultProp)
	{
		// Garbage collection does not touch root objects
		NewDefaultProp->AddToRoot();
		if (DefaultProp)
		{
			// Need to make sure to remove them again, very much like new / delete
			DefaultProp->RemoveFromRoot();
		}
		DefaultProp = NewDefaultProp;
	}
}

void UCommDistributor::EndPlay()
{
	if (DefaultProp) DefaultProp->RemoveFromRoot();
	DefaultProp = nullptr;
	PropagateList.Empty();
	ChannelList.Empty();
}
