#include "Configurator.h"
#include "rapidxml_utils.hpp"
#include "MessageDialog.h"

UConfigBase* UConfigurator::LoadConfig(std::string Filename)
{
	using namespace rapidxml;
	xml_document<> Doc;
	UConfigBase* ConfigObject = nullptr;

	// Read in and parse file
	try
	{
		file<> ConfigFile(Filename.c_str());
		Doc.parse<0>(ConfigFile.data());
	}
	catch (std::runtime_error error)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("A config file could not be found. File: ") + FString(Filename.c_str())));
		return nullptr;
	}
	catch (parse_error error)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("The config file is not valid RapidXML. File: ") + FString(Filename.c_str())));
		return nullptr;
	}

	// Construct the config object as the appropriate config class
	std::string FirstNodeName = Doc.first_node()->name();
	if (FirstNodeName == "Agent")
	{
		ConfigObject = NewObject<UAgentConfig>();
	}
	else if (FirstNodeName == "Scenario")
	{
		ConfigObject = NewObject<UScenarioConfig>();
	}

	if (ConfigObject != nullptr)
	{
		// Initialize the config object from the xml doc
		if (!ConfigObject->InitializeFromXML(Doc))
		{
			return nullptr;
		}
		ConfigObject->SetFileLocation(Filename.c_str());
	}
	return ConfigObject;

}

void UConfigurator::SaveConfig(std::string Filename, UConfigBase* Config)
{
	using namespace rapidxml;
	xml_document<> Doc;

	Doc.append_node(Config->GetXMLNode());

	// Print output to file
	std::ofstream File;
	File.open(Filename, std::ios::out | std::ios::trunc);

	if (File.is_open())
	{
		File << Doc;
	}

	File.close();

}

void UConfigurator::ReloadConfig(UConfigBase* Config)
{
	if (Config != nullptr)
	{
		using namespace rapidxml;
		UConfigBase* NewConfig = LoadConfig(TCHAR_TO_UTF8(*(Config->GetFileLocation())));
		if (NewConfig != nullptr)
		{
			// Set pointer to new object, old one will get cleaned up by Unreal
			Config = NewConfig;
		}
	}
}
