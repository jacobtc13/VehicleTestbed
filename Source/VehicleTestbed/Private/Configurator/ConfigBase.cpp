#include "ConfigBase.h"

UConfigBase::UConfigBase() : UObject()
{
}


UConfigBase::~UConfigBase()
{
}

rapidxml::xml_node<>* UConfigBase::GetXMLNode() const
{
	check(0 && "You must override this");
	return nullptr;
}

bool UConfigBase::InitializeFromXML(rapidxml::xml_document<>& doc)
{
	check(0 && "You must override this");
	return false;
}

bool UConfigBase::Instantiate(UObject* ContextObject)
{
	check(0 && "You must override this");
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
