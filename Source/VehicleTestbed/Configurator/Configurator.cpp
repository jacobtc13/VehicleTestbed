#include "Configurator.h"

UAgentConfig* UConfigurator::LoadAgentConfig(std::string Filename)
{
	using namespace rapidxml;
	xml_document<> doc;

	UAgentConfig* AgentConfig = NewObject<UAgentConfig>();

	// Read in and parse file
	std::ifstream is(Filename, std::ifstream::binary);
	if (is)
	{
		// find length of file
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		char* buffer = new char[length];

		is.read(buffer, length);

		is.close();

		doc.parse<0>(buffer);

		delete[] buffer;
	}
	else
	{
		// error occured reading file
	}
	// TODO: define code for decoding the DOM and setting the parameters of the AgentConfig

	return AgentConfig;

}

void UConfigurator::SaveAgentConfig(std::string Filename, UAgentConfig* AgentConfig)
{
	using namespace rapidxml;
	xml_document<> doc;

	doc.append_node(AgentConfig->GetXMLNode());

	// Print doc to string
	std::string output;
	print(std::back_inserter(output), doc, 0);

	// Print output to file
	std::ofstream file;
	file.open(Filename, std::ios::out | std::ios::trunc);

	if (file.is_open())
	{
		file << output;
	}

	file.close();

}
