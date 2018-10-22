#include "CommDistributor.h"

// static initialization
TArray<UCommChannel> UCommDistributor::ChannelList;
TArray<USNRModelFrequencyRange> UCommDistributor::PropagateList;
ISNRModel* UCommDistributor::DefaultProp = nullptr;

//TODO: Needs to populate the propergateList that the user has defined.

//Sends the message to the designated channel.
void UCommDistributor::Send(const IMessage& Message, IMessageSender* Sender, float Variance)
{
	if (CheckForMultiChannels(Sender->GetFrequency(), Variance))
	{
		for (const UCommChannel& Channel : GetChannels(Sender->GetFrequency(), Variance))
		{
			Channel.Broadcast(Message);
		}
	}
	else
	{
		// Log Event - The channel the sender want to broadcast does not exist.
	}

}

//Adds a UMessageReceiver to a specific channel, Also creates a channel non-existant
void UCommDistributor::AddToChannel(float Frequency, IMessageReceiver* Receiver)
{
	//Channel does not exist
	if (!CheckForChannel(Frequency))
	{
		CreateChannel(Frequency);
	}
	for (UCommChannel& Channel : GetChannels(Frequency, 0))
	{
		//package the input reciever into a TArray of IMessageReceivers
		TArray<IMessageReceiver*> temp;
		temp.AddUnique(Receiver);

		Channel.AddReceivers(temp);
	}
}

//Removes UMessageReceiver from a specific Channel
void UCommDistributor::RemoveFromChannel(float Frequency, IMessageReceiver* Receiver)
{
	for (UCommChannel& Channel : GetChannels(Frequency, 0))
	{
		//package the input reciever into a TArray of UMessageReceivers
		TArray<IMessageReceiver*> temp;
		temp.AddUnique(Receiver);

		Channel.RemoveReceivers(temp);
	}
}


void UCommDistributor::SwitchChannel(float Frequency, IMessageReceiver* Receiver)
{
	RemoveFromChannel(Receiver->GetFrequency(), Receiver);
	AddToChannel(Frequency, Receiver);
}

//Checks if a single channel exist
bool UCommDistributor::CheckForChannel(float Frequency)
{
	//Check if there are any channels at all
	if (ChannelList.Num() != 0)
	{
		//Check if the channel exists
		for (const UCommChannel& Channel : ChannelList)
		{
			//Channel exists
			if (Channel.GetFrequency() == Frequency)
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
		for (const UCommChannel& Channel : ChannelList)
		{
			if (Channel.GetFrequency() >= LowerRange && Channel.GetFrequency() <= UpperRange)
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
	//Creates a new channel with the associated SNRModel
	TArray<USNRModelFrequencyRange> SNRRanges = RetrieveSNRRange(Frequency);
	for (const USNRModelFrequencyRange& Range : SNRRanges)
	{
		ChannelList.AddUnique(UCommChannel(Frequency, Range.GetSNRModel()));
	}
}

//Retrieves an array of channels that are in the frequency range
TArray<UCommChannel> UCommDistributor::GetChannels(float Frequency, float Variance)
{
	TArray<UCommChannel> Output;
	float UpperRange = Frequency + Variance;
	float LowerRange = Frequency - Variance;
	for (const UCommChannel& Channel : ChannelList)
	{
		if (Channel.GetFrequency() >= LowerRange && Channel.GetFrequency() <= UpperRange)
		{
			Output.Add(Channel);
		}
	}
	return Output;
}

//Retrieves the SNR Model Frequency Range from the list
TArray<USNRModelFrequencyRange> UCommDistributor::RetrieveSNRRange(float Frequency)
{
	TArray<USNRModelFrequencyRange> Output;
	for (const USNRModelFrequencyRange& Range : PropagateList)
	{
		if (Range.GetMaxFrequency() >= Frequency && Range.GetMinFrequency() <= Frequency)
		{
			Output.AddUnique(Range);
		}
	}
	return Output;
}
