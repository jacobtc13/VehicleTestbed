#pragma once

#include "Message.h"

template <class M>
class TMessageTemplate : public IMessage
{
public:
	typedef M MessageType;

	TMessageTemplate(const MessageType& aMessage)
		: Message(aMessage)
	{}

	const MessageType& Get() const
	{
		return Message;
	}

private:
	const MessageType Message;
};
