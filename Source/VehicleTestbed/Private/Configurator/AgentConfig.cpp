#include "AgentConfig.h"
#include "UObjectIterator.h"
#include "GameFramework/GameState.h"

TArray<TSubclassOf<ATestbedWheeledVehicle>> UAgentConfig::AgentClasses;
TArray<TSubclassOf<AGadget>> UAgentConfig::Gadgets;

void UAgentConfig::AppendDocument(rapidxml::xml_document<>& OutDocument) const
{
	using namespace rapidxml;

	xml_node<>* BaseNode = OutDocument.allocate_node(node_element, "Agent");
	OutDocument.append_node(BaseNode);

	xml_node<>* ClassNode = OutDocument.allocate_node(node_element, "Class", OutDocument.allocate_string(TCHAR_TO_UTF8(*AgentClassName.ToString())));
	BaseNode->append_node(ClassNode);
	xml_node<>* NameNode = OutDocument.allocate_node(node_element, "Name", OutDocument.allocate_string(TCHAR_TO_UTF8(*AgentName.ToString())));
	BaseNode->append_node(NameNode);
	xml_node<>* PossessNode = OutDocument.allocate_node(node_element, "Possess", OutDocument.allocate_string(bPosessAtStart ? "true" : "false"));
	BaseNode->append_node(PossessNode);
	xml_node<>* GadgetsNode = OutDocument.allocate_node(node_element, "Gadgets");
	BaseNode->append_node(GadgetsNode);
	for (const FName& GadgetName : GadgetsOnThisAgent)
	{
		xml_node<>* GadgetNode = OutDocument.allocate_node(node_element, "Gadget");
		GadgetsNode->append_node(GadgetNode);
		xml_node<>* GadgetNameNode = OutDocument.allocate_node(node_element, "Name", OutDocument.allocate_string(TCHAR_TO_UTF8(*GadgetName.ToString())));
		GadgetNode->append_node(GadgetNameNode);
	}
}

bool UAgentConfig::InitializeFromXML(rapidxml::xml_document<>& Document)
{
	using namespace rapidxml;

	xml_node<>* Node = Document.first_node();
	if (!Node || ((std::string)Node->name() != "Agent"))
	{
		return false;
	}

	// Get class
	Node = Node->first_node();
	if (Node && ((std::string)Node->name() == "Class"))
	{
		SetAgentClassName(Node->value());
		// Check that the set worked
		if (GetAgentClassName() == FName())
		{
			return false;
		}
	}
	else return false;

	// Get the agent name
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "Name"))
	{
		SetAgentName(Node->value());
	}
	else return false;

	// Get possession bool
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "Possess"))
	{
		if ((std::string)Node->value() == "true")
		{
			SetPossessAtStart(true);
		}
		else if ((std::string)Node->value() == "false")
		{
			SetPossessAtStart(false);
		}
		else return false;
	}
	else return false;

	// Get gadgets
	Node = Node->next_sibling();
	if (Node && ((std::string)Node->name() == "Gadgets"))
	{
		for (xml_node<>* GadgetNode = Node->first_node(); GadgetNode && ((std::string)GadgetNode->name() == "Gadget"); GadgetNode = GadgetNode->next_sibling())
		{
			xml_node<>* GadgetNameNode = GadgetNode->first_node();
			if (GadgetNameNode && ((std::string)GadgetNameNode->name() == "Name"))
			{
				int32 GadgetArraySize = GadgetsOnThisAgent.Num();
				AddGadget(GadgetNameNode->value());
				if (!(GadgetsOnThisAgent.Num() > GadgetArraySize))
				{
					// Gadget name wasn't added to the array
					return false;
				}
			}
			else return false;
		}
	}
	else return false;

	return true;
}

bool UAgentConfig::Instantiate(UObject* ContextObject)
{
	if (!ContextObject || !ContextObject->ImplementsGetWorld())
	{
		return false;
	}

	UClass* Class = nullptr;
	for (UClass* AgentClass : AgentClasses)
	{
		if (AgentClass->GetFName() == GetAgentClassName())
		{
			Class = AgentClass;
			break;
		}
	}
	if (!Class) return false;
	ATestbedWheeledVehicle* NewAgent = NewObject<ATestbedWheeledVehicle>(UGameplayStatics::GetGameState(ContextObject)->GetLevel(), Class, GetAgentName());
	for (const FName& GadgetName : GadgetsOnThisAgent)
	{
		for (const TSubclassOf<AGadget>& GadgetClass : Gadgets)
		{
			if (GadgetClass->GetFName() == GadgetName)
			{
				// TODO: Un-hard code this
				if (GadgetName == TEXT("ShieldCountermeasure"))
				{
					NewAgent->MountGadget(GadgetClass, NewAgent->GetMountingNodeBySocketName(TEXT("ShieldSocket"))->GetMeshSocket());
				}
				else if (GadgetName == ("ProjectileCountermeasure"))
				{
					NewAgent->MountGadget(GadgetClass, NewAgent->GetMountingNodeBySocketName(TEXT("TurretSocket"))->GetMeshSocket());
				}
				else return false;
				break;
			}
		}
	}

	Agent = NewAgent;

	return true;
}

TArray<FName> UAgentConfig::GetAgentClassNames()
{
	if (!AgentClasses.Num())
	{
		InitializeAgentClassArray();
	}

	TArray<FName> Names;
	for (const UClass* Class : Gadgets)
	{
		Names.Add(Class->GetFName());
	}
	return Names;
}

FName UAgentConfig::GetAgentClassName() const
{
	return AgentClassName;
}

UClass* UAgentConfig::GetAgentClass() const
{
	if (!AgentClasses.Num())
	{
		InitializeAgentClassArray();
	}
	for (UClass* AgentClass : AgentClasses)
	{
		if (AgentClass->GetFName() == AgentClassName)
		{
			return AgentClass;
		}
	}
	return nullptr;
}

void UAgentConfig::SetAgentClassName(const FName& NewClassName)
{
	if (!AgentClasses.Num())
	{
		InitializeAgentClassArray();
	}
	for (const UClass* AgentClass : AgentClasses)
	{
		if (AgentClass->GetFName() == NewClassName)
		{
			AgentClassName = NewClassName;
			return;
		}
	}
}

FName UAgentConfig::GetAgentName() const
{
	return AgentName;
}

void UAgentConfig::SetAgentName(const FName& NewAgentName)
{
	AgentName = NewAgentName;
}

bool UAgentConfig::GetPossessAtStart() const
{
	return bPosessAtStart;
}

void UAgentConfig::SetPossessAtStart(const bool ShouldPossessAtStart)
{
	bPosessAtStart = ShouldPossessAtStart;
}

TArray<FName> UAgentConfig::GetGadgetsOnThisAgent() const
{
	return GadgetsOnThisAgent;
}

void UAgentConfig::AddGadget(const FName& GadgetName)
{
	if (!Gadgets.Num())
	{
		InitializeGadgetsArray();
	}
	for (const UClass* GadgetClass : Gadgets)
	{
		if (GadgetClass->GetFName() == GadgetName)
		{
			GadgetsOnThisAgent.Add(GadgetName);
			return;
		}
	}
}

void UAgentConfig::RemoveGadget(const FName& GadgetName)
{
	GadgetsOnThisAgent.Remove(GadgetName);
}

ATestbedWheeledVehicle* UAgentConfig::GetAgent() const
{
	return Agent;
}

TArray<TSubclassOf<AGadget>> UAgentConfig::GetGadgetClasses()
{
	if (!Gadgets.Num())
	{
		InitializeGadgetsArray();
	}
	return Gadgets;
}

void UAgentConfig::InitializeAgentClassArray()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		UClass* Class = *ClassIterator;

		if (!Class->IsChildOf<ATestbedWheeledVehicle>() || Class->HasAnyClassFlags(CLASS_Abstract))
		{
			continue;
		}

		if (Class->GetName().StartsWith(TEXT("SKEL_")) || Class->GetName().StartsWith(TEXT("REINST_")))
		{
			continue;
		}

		AgentClasses.Add(Class);
	}
}

void UAgentConfig::InitializeGadgetsArray()
{
	for (TObjectIterator<UClass> ClassIterator; ClassIterator; ++ClassIterator)
	{
		UClass* Class = *ClassIterator;

		if (!Class->IsChildOf<AGadget>() || Class->HasAnyClassFlags(CLASS_Abstract))
		{
			continue;
		}

		if (Class->GetName().StartsWith(TEXT("SKEL_")) || Class->GetName().StartsWith(TEXT("REINST_")))
		{
			continue;
		}

		Gadgets.Add(Class);
	}
}
