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

FString UConfigBase::GetFileLocation() const
{
	return FileLocation;
}

void UConfigBase::SetFileLocation(const FString& NewLocation)
{
	FileLocation = NewLocation;
}
