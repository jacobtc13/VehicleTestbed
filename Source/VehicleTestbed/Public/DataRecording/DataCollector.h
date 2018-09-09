// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataValue.h"

/// <summary>Abstract base DataCollector. Used to obtain pointers to concrete children
/// without knowing their type</summary>
class VEHICLETESTBED_API DataCollectorBase
{

public:
	///<summary>Default constructor, initialse with blank name and enabled = true</summary>
	DataCollectorBase();

	///<summary>Name constructor, initialse with set name and enabled = true</summary>
	DataCollectorBase(FName name);

	///<summary>Full constructor, initialse with called params</summary>
	DataCollectorBase(FName name, bool bEnable);

	///<summary>Virtual Print Method, collects the datavalue
	///<para>PURE VIRTUAL METHOD: Must be overriden in derived classes</para></summary>
	///<returns>Unique ptr to <see cref="DataValueBase"/></returns>
	virtual std::unique_ptr<DataValueBase> Collect() const = 0;

	///<summary>Setter method for enabled flag</summary>
	virtual void SetEnabled(bool bEnable);

	///<summary>Get enabled condition</summary>
	///<returns>Boolean enabled flag</summary>
	virtual bool IsEnabled() const;

	///<summary>Gets the name of collector</summary>
	///<returns>FName of the collector</returns>
	virtual FName GetName() const;

protected:
	bool bEnabled;
	FName Name;
};

/// <summary>Templated DataCollector Class. Allows any datacollector type to be held in a single vector</summary>
/// <example>Usage example
/// <code><![CDATA[
/// DataCollector<int> myCollector = new DataCollector<int>();
/// myCollector->FGetDelegate.BindUObject(this, &SomeClass::GetSomeInt);
/// ]]></code>
/// </example>
template <typename T>
class VEHICLETESTBED_API DataCollector : public DataCollectorBase
{
	DECLARE_DELEGATE_RetVal(T, FTypeDelegate)

public:
	FTypeDelegate FGetDelegate;

	///<summary>Default constuctor, calls base class default</summary>
	DataCollector();

	///<summary>Name constuctor, calls base class name ctor</summary>
	DataCollector(FName name);

	///<summary>Full constuctor, calls base class full ctor</summary>
	DataCollector(FName name, bool bEnable);

	///<summary>virtual destructor</summary>
	virtual ~DataCollector();

	///<summary>Collects the datavalue if delegate is bound</summary>
	///<returns>Unique pointer to <see cref="DataValueBase"/> object with value</returns>
	virtual std::unique_ptr<DataValueBase> Collect() const override;
};


template <typename T>
DataCollector<T>::DataCollector() : DataCollectorBase()
{
}

template <typename T>
DataCollector<T>::DataCollector(FName name) : DataCollectorBase(name)
{
}

template <typename T>
DataCollector<T>::DataCollector(FName name, bool bEnable) : DataCollectorBase(name, bEnable)
{
}

template <typename T>
DataCollector<T>::~DataCollector()
{

}

template <typename T>
std::unique_ptr<DataValueBase> DataCollector<T>::Collect() const
{
	std::unique_ptr<DataValueBase> ptr;
	DataValue<T> dataValue;
	if (FGetDelegate.IsBound())
	{
		T value = FGetDelegate.Execute();
		dataValue = DataValue<T>(value);
	}
	ptr = std::make_unique<DataValue<T>>(dataValue);
	return ptr;
}