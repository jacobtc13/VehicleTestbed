#pragma once

#include <list>
#include "MessageReceiver.h"

class FCommChannel
{
public:


private:
	float frequency;
	std::list<UMessageReceiver> receivers;
};