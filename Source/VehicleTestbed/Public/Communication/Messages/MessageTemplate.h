#pragma once

#include "Message.h"

///<summary>A helpful class to pass information through the communications system without needing to define a new <see cref="UMessage"> derived class</summary>
///<typeparam name="M">The type of the information being sent</typeparam>
template <class M>
class TMessageTemplate : public UMessage
{
public:
	typedef M MessageType;

	///<summary>Constructor which sets the message carried by this object</summary>
	///<param name="aMessage">The message to carry</param>
	TMessageTemplate(const MessageType& aMessage)
		: Message(aMessage)
	{}

	UFUNCTION(BlueprintGetter)
	///<summary>Getter for the carried message</summary>
	///<returns>The carried message</returns>
	const MessageType& Get() const
	{
		return Message;
	}

private:
	UPROPERTY(BlueprintGetter=Get)
	const MessageType Message;
};
