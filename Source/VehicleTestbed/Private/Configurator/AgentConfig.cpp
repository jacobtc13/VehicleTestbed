#include "AgentConfig.h"



UAgentConfig::UAgentConfig()
{
}


UAgentConfig::~UAgentConfig()
{
}

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
