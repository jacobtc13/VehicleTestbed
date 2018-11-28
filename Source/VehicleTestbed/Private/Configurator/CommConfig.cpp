#include "CommConfig.h"
#include "UObjectIterator.h"
#include "CommDistributor.h"

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

	// Check is a scenario
	xml_node<>* OuterNode = Doc.first_node("Communication");
	if (!OuterNode) return false;

	xml_node<>* ContentNode = nullptr;

	// Get default snr model
	ContentNode = OuterNode->first_node("DefaultModel");
	if (ContentNode && IsClassNameValidSNRModel(ContentNode->value()))
	{
		SetDefaultModelName(ContentNode->value());
	}
	else return false;

	// Get the frequency ranges
	ContentNode = OuterNode->first_node("FrequencyRanges");
	if (ContentNode)
	{
		for (xml_node<>* FrequencyNode = ContentNode->first_node("FrequencyRange"); FrequencyNode; FrequencyNode = FrequencyNode->next_sibling("FrequencyRange"))
		{
			FFrequencyRangeStruct FrequencyRange;

			// Get snr model for this range
			xml_node<>* InnerNode = FrequencyNode->first_node("SNRModel");
			if (InnerNode && IsClassNameValidSNRModel(InnerNode->value()))
			{
				FrequencyRange.ModelName = InnerNode->value();
			}
			else return false;

			// Get min frequency for this range
			InnerNode = FrequencyNode->first_node("MinFrequency");
			if (InnerNode)
			{
				FrequencyRange.MinFrequency = FCString::Atof(UTF8_TO_TCHAR(InnerNode->value()));
			}
			else return false;

			// Get max frequency for this range
			InnerNode = FrequencyNode->first_node("MaxFrequency");
			if (InnerNode)
			{
				FrequencyRange.MaxFrequency = FCString::Atof(UTF8_TO_TCHAR(InnerNode->value()));
			}
			else return false;

			AddFrequencyRange(FrequencyRange);
		}
	}
	else return false;

	return true;
}

bool UCommConfig::Instantiate(UObject* ContextObject)
{
	if (!ContextObject || !ContextObject->ImplementsGetWorld())
	{
		return false;
	}

	TArray<USNRModel*> SNRModelsMadeSoFar;

	// Set the default propagation model in the CommDistributor
	if (UClass* SNRModelClass = GetSNRModelClass(GetDefaultModelName()))
	{
		USNRModel* SNRModel = NewObject<USNRModel>((UObject*)GetTransientPackage(), SNRModelClass);
		SNRModelsMadeSoFar.Add(SNRModel);
		UCommDistributor::SetDefaultPropagation(SNRModel);
	}
	else return false;

	// Add the frequency ranges
	for (const auto& FrequencyRangeStruct : FrequencyRanges)
	{
		if (UClass* SNRModelClass = GetSNRModelClass(FrequencyRangeStruct.ModelName))
		{
			USNRModel* SNRModel = nullptr;
			// Check that an object of this SNRModel class doesn't already exist
			bool found = false;
			for (const auto& Model : SNRModelsMadeSoFar)
			{
				if (Model->StaticClass() == SNRModelClass)
				{
					SNRModel = Model;
					found = true;
					break;
				}
			}
			if (!found)
			{
				SNRModel = NewObject<USNRModel>((UObject*)GetTransientPackage(), SNRModelClass);
				SNRModelsMadeSoFar.Add(SNRModel);
			}
			USNRModelFrequencyRange* FrequencyRange = NewObject<USNRModelFrequencyRange>();
			FrequencyRange->Initialize(FrequencyRangeStruct.MinFrequency, FrequencyRangeStruct.MaxFrequency, SNRModel);
			UCommDistributor::AddSNRModelForFrequencyRange(FrequencyRange);
		}
		else return false;
	}

	return true;
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

UClass* UCommConfig::GetSNRModelClass(const FName& ModelName)
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
			return *Class;
		}
	}
	return nullptr;
}

bool FFrequencyRangeStruct::operator==(const FFrequencyRangeStruct& Other) const
{
	return ((ModelName == Other.ModelName) &&
		(MinFrequency == Other.MinFrequency) &&
		(MaxFrequency == Other.MaxFrequency));
}
