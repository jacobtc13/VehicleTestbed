#include "CommConfig.h"
#include "UObjectIterator.h"

TArray<TSubclassOf<USNRModel>> UCommConfig::SNRModels;

void UCommConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;

	OutDocument.clear();
	xml_node<>* BaseNode = OutDocument.allocate_node(node_element, "Communication");
	OutDocument.append_node(BaseNode);


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

FString UCommConfig::GetDefaultModelName() const
{
	return FString();
}

void UCommConfig::SetDefaultModelName(const FString& NewDefaultProp)
{}

TArray<FFrequencyRangeStruct> UCommConfig::GetFrequenyRanges() const
{
	return TArray<FFrequencyRangeStruct>();
}

void UCommConfig::AddFrequencyRange(const FFrequencyRangeStruct& FrequencyRange)
{}

bool UCommConfig::RemoveFrequencyRange(const FFrequencyRangeStruct& FrequencyRange)
{
	return false;
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

bool FFrequencyRangeStruct::operator==(const FFrequencyRangeStruct& Other)
{
	return ((ModelName == Other.ModelName) &&
		(MinFrequency == Other.MinFrequency) &&
		(MaxFrequency == Other.MaxFrequency));
}
