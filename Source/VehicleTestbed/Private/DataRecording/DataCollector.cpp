// Fill out your copyright notice in the Description page of Project Settings.

#include "DataCollector.h"

DataCollectorBase::DataCollectorBase() : Name(TEXT("")), bEnabled(true)
{
}

DataCollectorBase::DataCollectorBase(FName name) : Name(name), bEnabled(true)
{
}

DataCollectorBase::DataCollectorBase(FName name, bool bEnable) : Name(name), bEnabled(bEnable)
{
}

void DataCollectorBase::SetEnabled(bool bEnable)
{
	bEnabled = bEnable;
}

bool DataCollectorBase::IsEnabled() const
{
	return bEnabled;
}

FName DataCollectorBase::GetName() const
{
	return Name;
}


