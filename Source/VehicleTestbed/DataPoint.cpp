#include "DataPoint.h"

void DataPoint::SetTimestamp()
{
	//Timestamp = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	Timestamp = 0;
}

DataPoint::DataPoint()
{
	SetTimestamp();
}

DataPoint::DataPoint(DataValue* dataValue)
{
	SetTimestamp();
	Data.push_back(dataValue);
}

DataPoint::DataPoint(const std::vector<DataValue*>& data)
{
	SetTimestamp();
	Data = data;
}

DataPoint::~DataPoint()
{
	for (int i = 0; i < Data.size(); i++)
	{
		delete Data[i];
	}
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

void DataPoint::AddData(DataValue* dataValue)
{
	Data.push_back(dataValue);
}

void DataPoint::AddData(std::vector<DataValue*> data)
{
	Data.insert(std::end(Data), std::begin(data), std::end(data));
}

std::ostream & operator<<(std::ostream & os, const DataPoint & dataPoint)
{
	// TODO: insert return statement here
	os << dataPoint.Timestamp << ',';
	for (int i = 0; i < dataPoint.Data.size(); i++)
	{
		os << *dataPoint.Data[i] << ',';
	}
	return os;
}
