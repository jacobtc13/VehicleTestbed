#pragma once

#include <functional>

class FTransmissionPowerDistributionModel
{
public:
	FTransmissionPowerDistributionModel(const std::function<float(float, float, float)>& function)
		: powerFunction(function)
	{}

	float CalculatePower(float transmissionPower, float targetFrequency, float actualFrequency)
	{
		return powerFunction(transmissionPower, targetFrequency, actualFrequency);
	}

private:
	std::function<float(float, float, float)> powerFunction;
};
