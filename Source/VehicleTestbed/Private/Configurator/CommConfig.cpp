#include "CommConfig.h"
#include "UObjectIterator.h"

TArray<TSubclassOf<USNRModel>> UCommConfig::SNRModels;

void UCommConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;

	OutDocument.clear();
	xml_node<>* BaseNode = OutDocument.allocate_node(node_element, "Communication");
	OutDocument.append_node(BaseNode);

	// Save the default snr model to use
	xml_node<>* DefaultModelNode = OutDocument.allocate_node(node_element, "DefaultModel", OutDocument.allocate_string(TCHAR_TO_UTF8(*DefaultModelName.ToString())));
	BaseNode->append_node(DefaultModelNode);

	// Save the list of frequency ranges
	xml_node<>* FrequencyRangeOuterNode = OutDocument.allocate_node(node_element, "FrequencyRanges");
	BaseNode->append_node(FrequencyRangeOuterNode);
	for (const auto& FrequencyRange : FrequencyRanges)
	{
		xml_node<>* FrequencyRangeNode = OutDocument.allocate_node(node_element, "FrequencyRange");
		FrequencyRangeOuterNode->append_node(FrequencyRangeNode);
		xml_node<>* FrequencyRangeModelNode = OutDocument.allocate_node(node_element, "SNRModel", OutDocument.allocate_string(TCHAR_TO_UTF8(*FrequencyRange.ModelName.ToString())));
		FrequencyRangeNode->append_node(FrequencyRangeModelNode);
		xml_node<>* FrequencyRangeMinFreqNode = OutDocument.allocate_node(node_element, "MinFrequency", OutDocument.allocate_string(TCHAR_TO_UTF8(*FString::SanitizeFloat(FrequencyRange.MinFrequency))));
		FrequencyRangeNode->append_node(FrequencyRangeMinFreqNode);
		xml_node<>* FrequencyRangeMaxFreqNode = OutDocument.allocate_node(node_element, "MaxFrequency", OutDocument.allocate_string(TCHAR_TO_UTF8(*FString::SanitizeFloat(FrequencyRange.MaxFrequency))));
		FrequencyRangeNode->append_node(FrequencyRangeMaxFreqNode);
	}
}

bool UCommConfig::InitializeFromXML(rapidxml::xml_document<>& Doc)
{
	using namespace rapidxml;
	xml_node<>* Node = Doc.first_node();

	// Check is a scenario
	if (Node && ((std::string)Node->name() != "Communication"))
	{
		return false;
	}
	return true;
}

bool UCommConfig::Instantiate(UObject* ContextObject)
{

	return false;
}

TArray<FName> UCommConfig::GetPropagationModelNames()
{
	TArray<FName> Names;
	if (!SNRModels.Num())
	{
		PopulateSNRModelsArray();
	}
	for (const auto& Class : SNRModels)
	{
		Names.Add(Class.Get()->GetFName());
	}

	return Names;
}

FName UCommConfig::GetDefaultModelName() const
{
	return DefaultModelName;
}

void UCommConfig::SetDefaultModelName(const FName& NewDefaultModelName)
{
	if (IsClassNameValidSNRModel(NewDefaultModelName))
	{
		DefaultModelName = NewDefaultModelName;
	}
}

TArray<FFrequencyRangeStruct> UCommConfig::GetFrequenyRanges() const
{
	return FrequencyRanges;
}

void UCommConfig::AddFrequencyRange(const FFrequencyRangeStruct& FrequencyRange)
{
	if (IsClassNameValidSNRModel(FrequencyRange.ModelName))
	{
		if (FrequencyRange.MinFrequency <= FrequencyRange.MaxFrequency)
		{
			FrequencyRanges.Add(FrequencyRange);
		}
	}
}

bool UCommConfig::RemoveFrequencyRange(const FFrequencyRangeStruct& FrequencyRange)
{
	// Uses the equality operator defined in the struct
	return FrequencyRanges.Remove(FrequencyRange);
}

void UCommConfig::PopulateSNRModelsArray()
{
	// Find all subclasses of USNRModel and populate the SNRModels array
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		UClass* Class = *ClassIterator;

		// Check this class is a subclass of USNRModel
		if (!Class->IsChildOf(USNRModel::StaticClass()) || Class->HasAnyClassFlags(CLASS_Abstract))
		{
			continue;
		}

		// Add this class
		SNRModels.Add(Class);
	}
}

bool UCommConfig::IsClassNameValidSNRModel(const FName& ModelName)
{
	if (!SNRModels.Num())
	{
		PopulateSNRModelsArray();
	}
	for (const auto& Class : SNRModels)
	{
		if (ModelName == Class.Get()->GetFName())
		{
			// found a matching snr model
			return true;
		}
	}
	return false;
}

bool FFrequencyRangeStruct::operator==(const FFrequencyRangeStruct& Other) const
{
	return ((ModelName == Other.ModelName) &&
		(MinFrequency == Other.MinFrequency) &&
		(MaxFrequency == Other.MaxFrequency));
}
