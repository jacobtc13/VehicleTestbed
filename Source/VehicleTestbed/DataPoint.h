#pragma once

#include "CoreMinimal.h"
#include "DataValue.h"
#include <string>
#include <vector>
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

class VEHICLETESTBED_API DataPoint
{
private:
	float Timestamp;
	std::vector<DataValue*> Data;
	int Size;
	void SetTimestamp();
public:
	static DataPoint NIL;

	DataPoint();
	DataPoint(DataValue* data);
	DataPoint(const std::vector<DataValue*>& data);
	~DataPoint();

	bool operator==(const DataPoint& other) const;
	bool operator!=(const DataPoint& other) const;
	void AddData(DataValue* dataValue);
	void AddData(std::vector<DataValue*> data);
	friend std::ostream& operator<<(std::ostream & os, const DataPoint& dataPoint);
};



