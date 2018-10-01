// Fill out your copyright notice in the Description page of Project Settings.

#include "SNRModelFrequencyRange.h"


// Add default functionality here for any ISNRModelFrequencyRange functions that are not pure virtual.

//Getters and setters
void ISNRModelFrequencyRange::SetMinFrequency(float value)
{
	ISNRModelFrequencyRange::minFrequency = value;
}

float ISNRModelFrequencyRange::GetMinFrequency()
{
	return ISNRModelFrequencyRange::minFrequency;
}

void ISNRModelFrequencyRange::SetMaxFrequency(float value)
{
	ISNRModelFrequencyRange::maxFrequency = value;
}

float ISNRModelFrequencyRange::GetMaxFrequency()
{
	return ISNRModelFrequencyRange::maxFrequency;
}

void ISNRModelFrequencyRange::SetSNRModel(ISNRModel value)
{
	ISNRModelFrequencyRange::model = value;
}

ISNRModel ISNRModelFrequencyRange::SetSNRModel()
{
	return model;
}