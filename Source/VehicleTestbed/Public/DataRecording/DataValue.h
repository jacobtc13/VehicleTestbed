// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <memory>

/// <summary>Abstract base DataValue. Used to obtain pointers to concrete children
/// without knowing their type</summary>
class VEHICLETESTBED_API DataValueBase
{
public:
	///<summary>Virtual Clone Method, creates a deep copy of the current object
	///<para>PURE VIRTUAL METHOD: Must be overriden in derived classes</para></summary>
	///<returns>New DataValueBase</returns>
	virtual std::unique_ptr<DataValueBase> Clone() const = 0;

	///<summary>Virtual Print Method, outputs to an <see cref="std::ostream"/>
	///<para>PURE VIRTUAL METHOD: Must be overriden in derived classes</para></summary>
	///<param name="os"><see cref="std::ostream"/> object to write to</param>
	virtual void Print(std::ostream& os) const = 0;

	///<summary>Overriden output operator, calls print method on object</summary>
	///<param name="os"><see cref="std::ostream"/> object to write to</param>
	///<param name="dataValue">DataValueBase object to write</param>
	///<returns><see cref="std::ostream"/> object</returns>
	friend std::ostream& operator<<(std::ostream& os, const DataValueBase& dataValue)
	{
		dataValue.Print(os);
		return os;
	}
};

/// <summary>Templated DataValue Class. Allows any datatype to be held in a single vector</summary>
/// <example>Usage example
/// <code><![CDATA[
/// DataValue<int> myIntValue(1);
/// DataValue<bool> myBoolValue(true);
/// cout << myIntValue << ' ' << myBoolValue; // returns "1 true"
/// ]]></code>
/// </example>
template <typename T>
class VEHICLETESTBED_API DataValue : public DataValueBase
{
public:
	///<summary>Default constructor, initalises value</summary>
	DataValue()
	{
		Value = T{};
	}

	///<summary>Default constructor</summary>
	///<param name="value">Value to assign</summary>
	DataValue(T value)
	{
		Value = value;
	}

	///<summary>Copy Constructor</summary>
	///<param name="otherDataValue">DataValue to copy</param>
	DataValue(DataValue<T> const& otherDataValue)
	{
		Value = otherDataValue.Value;
	}

	///<summary>Destructor</summary>
	virtual ~DataValue() {};

	///<summary>Virtual Clone Method, creates a deep copy of the current object</summary>
	///<returns>New DataValue of current type</returns>
	virtual std::unique_ptr<DataValueBase> Clone() const
	{
		return std::make_unique<DataValue<T>>(*this);
	}

	///<summary>Virtual Print Method, outputs to an <see cref="std::ostream"/></summary>
	///<param name="os"><see cref="std::ostream"/> object to write to</param>
	void Print(std::ostream& os) const override
	{
		if (Value)
			os << Value;
	}

private:
	T Value;

};
