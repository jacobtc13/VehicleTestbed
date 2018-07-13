// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <memory>
/**
*
*/

class VEHICLETESTBED_API DataValueBase
{
public:
	virtual DataValueBase *Clone() const = 0;
	virtual void Print(std::ostream& os) const = 0;
	friend std::ostream& operator<<(std::ostream& os, const DataValueBase& dataValue)
	{
		dataValue.Print(os);
		return os;
	}
};

template <typename T>
class VEHICLETESTBED_API DataValue : public DataValueBase
{
private:
	T Value;
public:
	DataValue(T value)
	{
		Value = value;
	}
	DataValue(DataValue<T> const& otherDataValue)
	{
		Value = otherDataValue.Value;
	}

	virtual ~DataValue() {};

	virtual DataValue<T> *Clone() const
	{
		return new DataValue<T>(*this);
	}

	void Print(std::ostream& os) const override
	{
		os << Value;
	}
};