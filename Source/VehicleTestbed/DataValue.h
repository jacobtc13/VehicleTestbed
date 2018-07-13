// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
/**
 * 
 */
class VEHICLETESTBED_API DataValue
{
private: 
	union {
		uint64 ui;
		int64 si;
		bool b;
		double d;
		//std::string s;
	};
	enum { UINT, SINT, BOOL, DOUBLE } DataType;
public:
	DataValue(uint64 value);
	DataValue(int64 value);
	DataValue(bool value);
	DataValue(double value);
	//DataValue(std::string value);
	~DataValue();

	friend std::ostream& operator<<(std::ostream & os, const DataValue& dataValue);
};
