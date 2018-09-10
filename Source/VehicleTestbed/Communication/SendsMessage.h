#pragma once

#include "TranceiverBase.h"
#include <functional>

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SendsMessage.generated.h"

UINTERFACE(MinimalAPI)
class USendsMessage : public UTranceiverBase
{
	GENERATED_BODY()
};

class VEHICLETESTBED_API ISendsMessage : public ITranceiverBase
{
	GENERATED_BODY()

protected:
	// typical lambdas of this type should look like:
	// [](float transmissionPower, float targetFrequency, float actualFrequency) { expressions }
	typedef std::function<float(float transmissionPower, float targetFrequency, float actualFrequency)> PowerFunction;

public:
	virtual void Initialization(float aFrequency, float aMaxSignalStrength, PowerFunction function);
	virtual void Send(const Message message, float signalStrength);

protected:
	float frequency;
	float maxSignalStrength;
	PowerFunction CalculatePower;

private:
	//TODO Add friend methods from CommunicationDistributor
	//friend void CommunicationDistributor::Send();
};

/* Example
class Test : public ISendsMessage
{
public:
	Test()
	{
		Initialization(1, 2, [](float transmissionPower, float targetFrequency, float actualFrequency)
		{
			return 1;
		});
	}
	void blah()
	{
		CalculatePower(2, 432423, 23432);
	}
};
*/
