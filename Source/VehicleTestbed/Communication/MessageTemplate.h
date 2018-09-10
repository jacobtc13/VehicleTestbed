#pragma once

#include "Message.h"

template <class Message>
class TMessageTemplate : public FMessage
{
public:
	typedef Message MessageType;

	TMessageTemplate(const Message& aMessage)
		: message(aMessage)
	{}

	const Message& Get() const
	{
		return message;
	}

private:
	const MessageType message;
};
