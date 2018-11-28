#include "ThirtyMetreSNR.h"

float UThirtyMetreSNR::CalculateSNR(const float SignalPower, const FVector& SenderPos, const FVector& ReceiverPos) const
{
	// Units are measured in cm
	return (FVector::Distance(SenderPos, ReceiverPos) < 3000) ? SignalPower : 0;
}
