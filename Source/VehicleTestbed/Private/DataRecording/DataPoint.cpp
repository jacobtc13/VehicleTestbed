#include "DataPoint.h"

void DataPoint::SetTimestamp()
{
	FString fstr = FDateTime::Now().ToString();
	Timestamp = std::string(TCHAR_TO_UTF8(*fstr));
}

DataPoint::DataPoint()
{
	SetTimestamp();
}

DataPoint::DataPoint(std::unique_ptr<DataValueBase> dataValue)
{
	SetTimestamp();
	Data.push_back(dataValue);
}

DataPoint::DataPoint(const DataPoint & otherDataPoint)
{
	Timestamp = otherDataPoint.Timestamp;
	for (unsigned int i = 0; i < otherDataPoint.Data.size(); i++)
	{
		std::unique_ptr<DataValueBase> copyDataValue = std::make_unique<DataValueBase>(otherDataPoint.Data[i]->Clone());
		AddData(copyDataValue);
	}
}

DataPoint & DataPoint::operator=(const DataPoint & otherDataPoint)
{
	if (&otherDataPoint != this) // suicide guard
	{
		// Delete this datapoint
		Data.clear();

		// Copy DataPoint
		Timestamp = otherDataPoint.Timestamp;
		for (unsigned int i = 0; i < otherDataPoint.Data.size(); i++)
		{
			std::unique_ptr<DataValueBase> copyDataValue = std::make_unique<DataValueBase>(otherDataPoint.Data[i]);
			AddData(copyDataValue);
		}
	}
	return *this;
}

DataPoint::~DataPoint() { }

DataPoint DataPoint::NIL;

bool DataPoint::operator==(const DataPoint& other) const
{
	return (Timestamp == other.Timestamp && Data == other.Data);
}

bool DataPoint::operator!=(const DataPoint& other) const
{
	return !(*this == other);
}

void DataPoint::AddData(std::unique_ptr<DataValueBase>& dataValue)
{
	Data.push_back(dataValue);
}

std::ostream & operator<<(std::ostream & os, const DataPoint & dataPoint)
{
	os << dataPoint.Timestamp << ',';
	for (unsigned int i = 0; i < dataPoint.Data.size(); i++)
	{
		os << *dataPoint.Data[i] << ',';
	}
	return os;
}
