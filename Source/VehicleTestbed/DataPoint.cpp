#include "DataPoint.h"

void DataPoint::SetTimestamp()
{
	static float count = 0;
	Timestamp = count++;
}

DataPoint::DataPoint()
{
	SetTimestamp();
}

DataPoint::DataPoint(DataValueBase* dataValue)
{
	SetTimestamp();
	Data.push_back(dataValue);
}

DataPoint::DataPoint(const DataPoint & otherDataPoint)
{
	Timestamp = otherDataPoint.Timestamp;
	for (unsigned int i = 0; i < otherDataPoint.Data.size(); i++)
	{
		AddData(otherDataPoint.Data[i]->Clone());
	}
}

DataPoint & DataPoint::operator=(const DataPoint & otherDataPoint)
{
	if (&otherDataPoint != this) // suicide guard
	{
		// Delete this datapoint
		for (unsigned int i = 0; i < Data.size(); i++)
		{
			delete Data[i];
		}

		// Copy DataPoint
		Timestamp = otherDataPoint.Timestamp;
		for (unsigned int i = 0; i < otherDataPoint.Data.size(); i++)
		{
			AddData(otherDataPoint.Data[i]->Clone());
		}
	}
	return *this;
}

DataPoint::~DataPoint()
{
}

DataPoint DataPoint::NIL;

bool DataPoint::operator==(const DataPoint& other) const
{
	return (Timestamp == other.Timestamp && Data == other.Data);
}

bool DataPoint::operator!=(const DataPoint& other) const
{
	return !(*this == other);
}

void DataPoint::AddData(DataValueBase* dataValue)
{

	Data.push_back(dataValue->Clone());
}

std::ostream & operator<<(std::ostream & os, const DataPoint & dataPoint)
{
	// TODO: insert return statement here
	os << dataPoint.Timestamp << ',';
	for (unsigned int i = 0; i < dataPoint.Data.size(); i++)
	{
		os << *dataPoint.Data[i] << ',';
	}
	return os;
}
