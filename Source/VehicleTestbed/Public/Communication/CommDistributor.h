#pragma once

#include "CoreMinimal.h"

#include "CommChannel.h"
#include "SNRModel.h"
#include "SNRModelFrequencyRange.h"
#include "Message.h"
#include "MessageSender.h"
#include "MessageReceiver.h"

#include "CommDistributor.generated.h"

UCLASS(Abstract)
class VEHICLETESTBED_API UCommDistributor : public UObject
{
	GENERATED_BODY()

public:
	///<summary>Sends a message to all receivers on the chosen frequency</summary>
	///<param name="Message">The message to send</param>
	///<param name="Sender">The sender of the message</param>
	///<param name="SignalPower">The signal strength of the message</param>
	static void Send(const IMessage& Message, UObject* Sender, float SignalPower);

	///<summary>Adds a receiver to a frequency</summary>
	///<param name="Frequency">The frequency to add to</param>
	///<param name="Receiver">The receiver to add</param>
	static void AddToChannel(float Frequency, UObject* Receiver);

	///<summary>Removes a receiver from a frequency</summary>
	///<param name="Frequency">The frequency to remove from</param>
	///<param name="Receiver">The receiver to remove</param>
	static void RemoveFromChannel(float Frequency, UObject* Receiver);

	///<summary>Checks if a channel exists in memory</summary>
	///<param name="Frequency">The frequency to check</param>
	///<returns>Whether the channel exists or not</returns>
	static bool CheckForChannel(float Frequency);

	///<summary>Checks if any channel exists within a range of frequencies</summary>
	///<param name="Frequency">The median of the range</param>
	///<param name="Variance">The value added and subtracted from the median to determine the min and max of the range</param>
	///<returns>Whether a channel exists in this range</returns>
	static bool CheckForMultiChannels(float Frequency, float Variance);

	///<summary>Creates a new channel for the specified frequency</summary>
	///<param name="Frequency">The frequency for this channel</param>
	static void CreateChannel(float Frequency);

	///<summary>Returns an array of channels within a range of frequencies</summary>
	///<param name="Frequency">The median of the range</param>
	///<param name="Variance">The value added and subtracted from the median to determine the min and max of the range</param>
	///<returns>An array of channels within the specified range</returns>
	static TArray<UCommChannel*> GetChannels(float Frequency, float Variance);

	///<summary>Changes which frequency a receiver is listening to</summary>
	///<param name="Frequency">The new frequency to listen to</param>
	///<param name="Receiver">The receiver to modify</param>
	static void SwitchChannel(float Frequency, UObject* Receiver);

	///<summary>Returns an array of frequency range objects that match the specified frequency</summary>
	///<param name="Frequency">The frequency to search for</param>
	///<returns>An array of frequency range objects that match the specified frequency</returns>
	static TArray<USNRModelFrequencyRange*> RetrieveSNRRange(float Frequency);

	// TODO: Connect with Comm config

protected:
	static TArray<UCommChannel*> ChannelList;
	static TArray<USNRModelFrequencyRange*> PropagateList;
	static TSharedPtr<USNRModel> DefaultProp;
};
