// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Queue.h"
#include "DataPoint.h"
#include "DataAsset.generated.h"

/**
 * 
 */
class VEHICLETESTBED_API DataCollector
{
private:
	
	Queue<DataPoint> DataQueue;
public:

	DataCollector();
	~DataCollector();
};
