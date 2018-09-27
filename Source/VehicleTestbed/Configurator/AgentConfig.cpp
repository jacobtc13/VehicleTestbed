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
	return doc.allocate_node(node_element, "Agent", "Default");
}
