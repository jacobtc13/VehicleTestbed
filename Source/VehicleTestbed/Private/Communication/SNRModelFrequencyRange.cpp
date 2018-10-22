#include "SNRModelFrequencyRange.h"
#include "VoidSNR.h"

USNRModelFrequencyRange::USNRModelFrequencyRange()
{}

//Getters and setters
void USNRModelFrequencyRange::SetMinFrequency(float NewMin)
{
	MinFrequency = NewMin;
}

float USNRModelFrequencyRange::GetMinFrequency() const
{
	return MinFrequency;
}

void USNRModelFrequencyRange::SetMaxFrequency(float NewMax)
{
	MaxFrequency = NewMax;
}

float USNRModelFrequencyRange::GetMaxFrequency() const
{
	return MaxFrequency;
}

void USNRModelFrequencyRange::SetSNRModel(USNRModel* NewSNR)
{
	Model = NewSNR;
}

USNRModel* USNRModelFrequencyRange::GetSNRModel() const
{
	return Model;
}
