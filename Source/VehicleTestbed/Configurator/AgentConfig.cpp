#include "AgentConfig.h"



UAgentConfig::UAgentConfig()
{
}


UAgentConfig::~UAgentConfig()
{
}

rapidxml::xml_node<>* UAgentConfig::GetXMLNode()
{
	using namespace rapidxml;
	xml_document<> doc;
	xml_node<>* baseNode = doc.allocate_node(node_element, "Agent");
	xml_node<>* classNode = doc.allocate_node(node_element, "Class", TCHAR_TO_UTF8(AgentClass));
	baseNode->append_node(classNode);
	xml_node<>* nameNode = doc.allocate_node(node_element, "Name", TCHAR_TO_UTF8(*AgentName));
	baseNode->append_node(nameNode);

	return baseNode;
}
