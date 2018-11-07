#include "CommConfig.h"

void UCommConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;
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
