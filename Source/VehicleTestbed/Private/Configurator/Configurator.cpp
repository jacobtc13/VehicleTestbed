#include "Configurator.h"
#include "AgentConfig.h"
#include "ScenarioConfig.h"
#include "CommConfig.h"

#include "rapidxml_utils.hpp"
#include "MessageDialog.h"

FString UConfigurator::Scenario;

void UConfigurator::StartScenario(UObject* ContextObject)
{
	// Try opening the scenario file
	if (UScenarioConfig* ScenarioConfig = Cast<UScenarioConfig>(LoadConfig(TCHAR_TO_UTF8(*Scenario))))
	{
		// Loaded file successfully
		if (ScenarioConfig->Instantiate(ContextObject))
		{
			return;
		}
	}
	// Failed to load the scenario, error already shown to user by LoadConfig()
	// Backtrack to the main menu
	UGameplayStatics::OpenLevel(ContextObject, TEXT("OpenerMap"));
}

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
		else if (FirstNodeName == "Communication")
		{
			ConfigObject = NewObject<UCommConfig>();
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
}

void UConfigurator::SaveConfig(std::string Filename, UConfigBase* Config)
{
	using namespace rapidxml;
	xml_document<> Doc;

	Config->AppendDocument(Doc);

	// Print output to file
	std::ofstream File(Filename);

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

FString UConfigurator::GetScenario()
{
	return Scenario;
}

void UConfigurator::SetScenario(FString ScenarioFile)
{
	Scenario = ScenarioFile;
}
