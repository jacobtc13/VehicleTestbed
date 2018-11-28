#pragma once

#include "Object.h"
#include "rapidxml.hpp"
#include <string>
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "ConfigBase.generated.h"

UCLASS(Abstract, BlueprintType)
class VEHICLETESTBED_API UConfigBase : public UObject
{
	GENERATED_BODY()

public:
	///<summary>Empty default constructor</summary>
	UConfigBase();

	///<summary>Empty virtual destructor</summary>
	virtual ~UConfigBase();

	///<summary>Attaches the xml structure which represents this config to the document</summary>
	///<param name="OutDocument">The xml document to append to</param>
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const;

	///<summary>Initializes this config object from an xml document</summary>
	///<param name="Document">The xml document to initialize from</param>
	///<returns>Whether this config object initialized correctly</returns>
	virtual bool InitializeFromXML(rapidxml::xml_document<>& Document);

	UFUNCTION(meta = (WorldContext = ContextObject))
	///<summary>Creates, initializes and/or spawns what this config object represents into the game world</summary>
	///<param name="ContextObject">A UObject which can provide world context</name>
	///<returns>Whether this config object was able to instantiate correctly</returns>
	virtual bool Instantiate(UObject* ContextObject);

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the file path for the xml file which represents this config object</summary>
	///<returns>A string represention of the file path</returns>
	FString GetFileLocation() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the file path for which file represents this config object</summary>
	///<param name="NewLocation">The new file path</param>
	void SetFileLocation(const FString& NewLocation);

protected:
	UPROPERTY(BlueprintGetter=GetFileLocation, BlueprintSetter=SetFileLocation)
	FString FileLocation;
};
