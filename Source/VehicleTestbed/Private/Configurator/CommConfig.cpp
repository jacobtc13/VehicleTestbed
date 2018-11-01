#include "CommConfig.h"

rapidxml::xml_node<>* UCommConfig::GetXMLNode() const
{
	return nullptr;
}

bool UCommConfig::InitializeFromXML(rapidxml::xml_document<>& doc)
{
	return false;
}

bool UCommConfig::Instantiate(UObject * ContextObject)
{
	return false;
}
