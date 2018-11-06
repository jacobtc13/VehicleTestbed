#include "AgentConfig.h"
#include "UObjectIterator.h"

TArray<TSubclassOf<AGadget>> UAgentConfig::Gadgets;

void UAgentConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;

	xml_node<>* baseNode = OutDocument.allocate_node(node_element, "Agent");
	OutDocument.append_node(baseNode);

	xml_node<>* classNode = OutDocument.allocate_node(node_element, "Class", TCHAR_TO_UTF8(AgentClass));
	baseNode->append_node(classNode);
	xml_node<>* nameNode = OutDocument.allocate_node(node_element, "Name", TCHAR_TO_UTF8(*AgentName));
	baseNode->append_node(nameNode);

}

bool UAgentConfig::InitializeFromXML(rapidxml::xml_document<>& Document)
{
	return false;
}

bool UAgentConfig::Instantiate(UObject* ContextObject)
{
	return false;
}

void UAgentConfig::InitializeGadgetsMap()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		UClass* Class = *ClassIterator;

		if (!Class->IsChildOf<AGadget>() || Class->HasAnyClassFlags(CLASS_Abstract))
		{
			continue;
		}

		Gadgets.Add(Class);
	}
}
