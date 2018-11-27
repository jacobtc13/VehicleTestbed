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

	xml_node<>* OuterNode = Document.first_node("Agent");
	if (!OuterNode) return false;

	xml_node<>* ContentNode = nullptr;

	// Get class
	ContentNode = OuterNode->first_node("Class");
	if (ContentNode)
	{
		SetAgentClassName(ContentNode->value());
		// Check that the set worked
		if (GetAgentClassName() == FName())
		{
			return false;
		}
	}
	else return false;

	// Get the agent name
	ContentNode = OuterNode->first_node("Name");
	if (ContentNode)
	{
		SetAgentName(ContentNode->value());
		// Don't need to check the value because it's okay if the name is empty
	}
	else return false;

	// Get possession bool
	ContentNode = OuterNode->first_node("Possess");
	if (ContentNode)
	{
		if ((std::string)ContentNode->value() == "true")
		{
			SetPossessAtStart(true);
		}
		else if ((std::string)ContentNode->value() == "false")
		{
			SetPossessAtStart(false);
		}
		else return false;
	}
	else return false;

	// Get gadgets
	ContentNode = OuterNode->first_node("Gadgets");
	if (ContentNode)
	{
		for (xml_node<>* GadgetNode = ContentNode->first_node("Gadget"); GadgetNode; GadgetNode = GadgetNode->next_sibling("Gadget"))
		{
			// Get the name of the gadget
			if (xml_node<>* GadgetNameNode = GadgetNode->first_node("Name"))
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

	// spawn the agent
	UClass* AgentClass = GetAgentClass();
	if (!AgentClass) return false;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Name = GetAgentName();

	ATestbedWheeledVehicle* SpawnedAgent = ContextObject->GetWorld()->SpawnActor<ATestbedWheeledVehicle>(AgentClass, PositionforNextSpawn, RotationForNextSpawn, SpawnParameters);
	if (GetPossessAtStart())
	{
		UGameplayStatics::GetPlayerController(ContextObject, 0)->Possess(SpawnedAgent);
	}
	for (const FName& GadgetName : GetGadgetsOnThisAgent())
	{
		for (const TSubclassOf<AGadget>& GadgetClass : UAgentConfig::GetGadgetClasses())
		{
			if (GadgetClass->GetFName() == GadgetName)
			{
				// TODO: Un-hard code this
				if (GadgetName == TEXT("ShieldCountermeasure"))
				{
					SpawnedAgent->MountGadget(GadgetClass, SpawnedAgent->GetMountingNodeBySocketName(TEXT("ShieldSocket"))->GetMeshSocket());
				}
				else if (GadgetName == ("ProjectileCountermeasure"))
				{
					SpawnedAgent->MountGadget(GadgetClass, SpawnedAgent->GetMountingNodeBySocketName(TEXT("TurretSocket"))->GetMeshSocket());
				}
				else return false;
				break;
			}
		}
	}
	return true;
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

FName UAgentConfig::GetAgentClassName() const
{
	return AgentClassName;
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

void UAgentConfig::SetNextSpawn(const FVector & NextPosition, const FRotator & NextRotation)
{
	PositionforNextSpawn = NextPosition;
	RotationForNextSpawn = NextRotation;
}

TArray<FName> UAgentConfig::GetAgentClassNames()
{
	if (!AgentClasses.Num())
	{
		InitializeAgentClassArray();
	}

	TArray<FName> Names;
	for (const UClass* Class : AgentClasses)
	{
		Names.Add(Class->GetFName());
	}
	return Names;
}

TArray<FName> UAgentConfig::GetGadgetClassNames()
{
	if (!Gadgets.Num())
	{
		InitializeGadgetsArray();
	}
	TArray<FName> Names;
	for (const UClass* Class : Gadgets)
	{
		Names.Add(Class->GetFName());
	}
	return Names;
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
