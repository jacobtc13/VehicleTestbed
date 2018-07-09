#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <time.h>

const time_t ctt = time(0);

template <typename T>
class VEHICLETESTBED_API DataPoint
{
private:
	std::string Timestamp;
	std::vector<T> Data;
	int Size;
	void SetTimestamp();
public:
	DataPoint();
	DataPoint(const T data);
	DataPoint(const std::vector<T>& data);
	~DataPoint();

	bool operator==(const DataPoint<T>& other) const;
	bool operator!=(const DataPoint<T>& other) const;
	void AddData(T aData);
	void AddData(std::vector<T> aData);
	friend std::ostream& operator<<(std::ostream & aOstream, const DataPoint<T>& aDataPoint)
	{
		aOstream << aDataPoint.fTimestamp << ',';
		for (uint16_t i = 0; i < aDataPoint.fData.size(); i++)
		{
			aOstream << aDataPoint.fData[i] << ',';
		}
		return aOstream;
	}
};

template <typename T>
void DataPoint<T>::SetTimestamp()
{
	time_t t = time(NULL);
	struct tm buf;
	char str[26];
	auto err = localtime_s(&buf, &t);
	asctime_s(str, 26, &buf);
	str[strlen(str) - 1] = '\0'; // remove trailling newline
	Timestamp = str;
}

template <typename T>
bool DataPoint<T>::operator==(const DataPoint<T>& other) const
{
	return (fTimestamp == other.fTimestamp && fData == other.fData);
}

template <typename T>
bool DataPoint<T>::operator!=(const DataPoint<T>& other) const
{
	return !(*this == other);
}

template <typename T>
DataPoint<T>::DataPoint()
{
	SetTimestamp();
}

template <typename T>
DataPoint<T>::DataPoint(const T aData)
{
	SetTimestamp();
	Data.push_back(aData);
}

template <typename T>
DataPoint<T>::DataPoint(const std::vector<T>& aData)
{
	SetTimestamp();
	Data = aList;
}

template <typename T>
DataPoint<T>::~DataPoint()
{
	free(Data);
}

template <typename T>
void DataPoint<T>::AddData(T data)
{
	Data.push_back(data);
}

template <typename T>
void DataPoint<T>::AddData(std::vector<T> data)
{
	Data.insert(std::end(Data), std::begin(data), std::end(data));
}
