#pragma once

#include <list>
#include "MessageReceiver.h"
#include "SNRModel.h"

class CommChannel
{

public:


private:
	float frequency;
	std::list<UMessageReceiver> receivers;
	SNRModel snrModel = new SNRModel();
};