#pragma once

#include "Message.h"

template <class M>
class TMessageTemplate : public UMessage
{
public:
	typedef M MessageType;

	TMessageTemplate(const MessageType& aMessage)
		: Message(aMessage)
	{}

	UFUNCTION()
	const MessageType& Get() const
	{
		return Message;
	}

private:
	UPROPERTY()
	const MessageType Message;
};
