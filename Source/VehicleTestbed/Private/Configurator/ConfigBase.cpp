#include "ConfigBase.h"

UConfigBase::UConfigBase() : UObject()
{
}


UConfigBase::~UConfigBase()
{
}

void UConfigBase::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	check(0 && "You must override this");
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
