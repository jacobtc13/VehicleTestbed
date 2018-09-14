#pragma once

#include "CoreMinimal.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "DataValue.h"


///<summary>DataPoint class for data recording queue, holds a timestamp and list of dataValues</summary>
class VEHICLETESTBED_API DataPoint 
{

public:
	///<summary>Default Constructor</summary>
	DataPoint();
	
	///<summary>Copy Constructor, create deep copy of other datapoint</summary>
	///<param name="otherDataPoint">Datapoint to copy</param>
	///<returns>New DataPoint with deep copy of otherDataPoint</returns>
	DataPoint(const DataPoint & otherDataPoint);

	///<summary>Assignment Operator, deep copy all values from other datapoint</summary>
	///<param name="otherDataPoint">Datapoint to copy</param>
	///<returns>This DataPoint with deep copy of otherDataPoint</returns>
	DataPoint& operator=(const DataPoint& otherDataPoint);

	///<summary>Destructor</summary>
	virtual ~DataPoint();

	///<summary>Equality operator, compares datapoints</summary>
	///<param name="other">Datapoint to compare</param>
	///<returns><see cref="bool" /> Equality</returns>
	bool operator==(const DataPoint& other) const;

	///<summary>Inequality operator, compares datapoints</summary>
	///<param name="other">Datapoint to compare</param>
	///<returns><see cref="bool" /> inequality</returns>
	bool operator!=(const DataPoint& other) const;

	///<summary>Adds a DataValue to the Data Vector</summary>
	void AddData(std::unique_ptr<DataValueBase> dataValue);

	///<summary>Output operator, writes DataPoint to <see cref="std::ostream"/></summary>
	friend std::ostream& operator<<(std::ostream & os, const DataPoint& dataPoint);

private:
	std::string Timestamp;
	std::vector<std::unique_ptr<DataValueBase>> Data;

	///<summary>Gets the timestamp from the environment and sets it</summary>
	void SetTimestamp();
};


