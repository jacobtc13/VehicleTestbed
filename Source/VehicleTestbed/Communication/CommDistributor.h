#pragma once

#include "Object.h"
#include <iostream>
//#include "CommDistributor.generated.h"
#include <list>
#include "CommChannel.h"
#include "SNRModel.h"

UCLASS()
class VEHICLETESTBED_API CommDistributor : public UObject
{
	GENERATED_BODY()

public:

	CommDistributor();

protected:
	std::list<CommChannel> channelList;
	SNRModel defaultPropModel;
	
};
