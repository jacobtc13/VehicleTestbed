#pragma once

#include <list>
#include "MessageReceiver.h"
#include "SNRModel.h"

class CommChannel
{

private:
	float frequency;
	TArray<UMessageReceiver> receivers;
	SNRModel snrModel;

public:
	float GetFrequency();

};