// Fill out your copyright notice in the Description page of Project Settings.

#include "DataValue.h"

DataValue::DataValue(uint64 value)
{
	ui = value;
	DataType = DataValue::UINT;
}

DataValue::DataValue(int64 value)
{
	si = value;
	DataType = DataValue::SINT;
}

DataValue::DataValue(bool value) 
{
	b = value;
	DataType = DataValue::BOOL;
}

DataValue::DataValue(double value)
{
	d = value;
	DataType = DataValue::DOUBLE;
}

//DataValue::DataValue(std::string value)
//{
//	s = value;
//	DataType = DataValue::STRING;
//}

DataValue::~DataValue() { }

std::ostream & operator<<(std::ostream & os, const DataValue & dataValue)
{
	// TODO: insert return statement here
	switch (dataValue.DataType) {
	case DataValue::UINT :
		os << dataValue.ui;
		break;
	case DataValue::SINT :
		os << dataValue.si;
		break;
	case DataValue::BOOL :
		os << dataValue.b;
		break;
	case DataValue::DOUBLE :
		os << dataValue.d;
		break;
	/*case DataValue::STRING :
		os << std::string(TCHAR_TO_UTF8(*dataValue.s));
		break;*/
	}
	return os;
}
