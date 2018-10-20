#include "ConfigBase.h"

UConfigBase::UConfigBase() : UObject()
{
}


UConfigBase::~UConfigBase()
{
}

rapidxml::xml_node<>* UConfigBase::GetXMLNode()
{
	return nullptr;
}

bool UConfigBase::InitializeFromXML(rapidxml::xml_document<>& doc)
{
	return false;
}

FString UConfigBase::GetFileLocation() const
{
	return FileLocation;
}

void UConfigBase::SetFileLocation(const FString& NewLocation)
{
	FileLocation = NewLocation;
}
