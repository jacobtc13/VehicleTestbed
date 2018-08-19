// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataValue.h"


class VEHICLETESTBED_API DataCollectorBase
{
private:
	bool bEnabled;
	FName Name;
public:
	///<summary>Virtual Print Method, collects the datavalue
	///<para>PURE VIRTUAL METHOD: Must be overriden in derived classes</para></summary>
	///<returns>Reference to <see cref="DataValueBase"/></returns>
	virtual std::unique_ptr<DataValueBase> Collect() const = 0;

	///<summary>Setter method for enabled flag</summary>
	virtual void SetEnabled(bool bEnable);
};

/**
 * 
 */
template <typename T>
class VEHICLETESTBED_API DataCollector : public DataCollectorBase
{
	DECLARE_DELEGATE_RetVal(T, FTypeDelegate)

public:
	FTypeDelegate FGetDelegate;
	DataCollector();
	virtual ~DataCollector();

	virtual std::unique_ptr<DataValueBase> Collect() const override;
};


template <typename T>
DataCollector<T>::DataCollector()
{
}

template <typename T>
DataCollector<T>::~DataCollector()
{

}

template <typename T>
std::unique_ptr<DataValueBase> DataCollector<T>::Collect() const
{
	DataValue<T> dataValue;
	if (FGetDelegate.IsBound())
	{
		T value = FGetDelegate.Execute();
		dataValue = DataValue<T>(value);
	}
	return std::make_unique<DataValueBase>(&dataValue);
}