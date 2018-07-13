#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "DataValue.h"

class VEHICLETESTBED_API DataPoint {
private:
	float Timestamp;
	std::vector<DataValueBase*> Data;
	int Size;
	void SetTimestamp();
public:
	static DataPoint NIL;

	DataPoint();
	DataPoint(DataValueBase* data);

	DataPoint(const DataPoint & otherDataPoint);
	DataPoint& operator=(const DataPoint& otherDataPoint);
	~DataPoint();

	bool operator==(const DataPoint& other) const;
	bool operator!=(const DataPoint& other) const;
	void AddData(DataValueBase* dataValue);
	friend std::ostream& operator<<(std::ostream & os, const DataPoint& dataPoint);
};


