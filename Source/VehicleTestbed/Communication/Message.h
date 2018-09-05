#pragma once

template <class M>
class FMessage
{
public:
	Message(M aMessage)
	{
		message = aMessage;
	}

	const M& Get() const
	{
		return &message;
	}

private:
	M message;
};
