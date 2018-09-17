#include "CommDistributor.h"


CommDistributor::CommDistributor()
{
	
}

//Sends the message to the designated channel.
void CommDistributor::Send(const FMessage<class T>&, UMessageSender sender, float frequency)
{
	//Check if there are any channels at all
	if (CommDistributor::channelList.IsValidIndex) 
	{
		if (CommDistributor::channelList.Num != 0)
		{
			//Check if the channel exists
			for (CommChannel channel : CommDistributor::channelList)
			{
				//Channel exists
				if (channel.GetFrequency == frequency)
				{
					//Send the message in that channel
					return;
				}
			}

			//Channel does not exist
			//TODO:Add functionality that adds a new Channel then send the message
		}
	}
	
	
}

void CommDistributor::Add(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this method add new channels into the TArray
}

void CommDistributor::Remove(SNRModelFrequencyRange freqRange)
{
	//TODO: Make this Method Remove the channels from the TArray
}

