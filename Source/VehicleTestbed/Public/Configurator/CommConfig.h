#pragma once

#include "ConfigBase.h"
#include "SNRModel.h"
#include "SubclassOf.h"

#include "CoreMinimal.h"
#include "CommConfig.generated.h"

USTRUCT(BlueprintType)
struct FFrequencyRangeStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ModelName;
	UPROPERTY(EditAnywhere)
	float MinFrequency;
	UPROPERTY(EditAnywhere)
	float MaxFrequency;

	bool operator==(const FFrequencyRangeStruct& Other) const;
};


UCLASS()
class VEHICLETESTBED_API UCommConfig : public UConfigBase
{
	GENERATED_BODY()

public:
	///<summary>Clears the passed in document and adds a node structure representing this object</summary>
	///<param name="OutDocument">The document to be populated</param>
	virtual void AppendDocument(rapidxml::xml_document<>& OutDocument) const override;

	///<summary>Initializes this config object from the passed in document</summary>
	///<param name="doc">The document to initialize from</param>
	///<returns>Whether the object successfully initialized from the document or not</returns>
	virtual bool InitializeFromXML(rapidxml::xml_document<>& doc) override;

	UFUNCTION(meta = (WorldContext = ContextObject))
	///<summary>Initializes the communications distributor</summary>
	///<param name="ContextObject">An object with which to provide world context</param>
	///<returns>Whether the communications distributor was initialized successfully</returns>
	virtual bool Instantiate(UObject* ContextObject) override;

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the names of all propagation models in the simulator</summary>
	///<returns>An array of names of the SNR Model classes</returns>
	TArray<FName> GetPropagationModelNames();

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the name of the default propagation model used in this config</summary>
	///<returns>The name of the default propagation model</returns>
	FName GetDefaultModelName() const;

	UFUNCTION(BlueprintSetter)
	///<summary>Sets the name of the default propagation model used in this config</summary>
	///<param name="NewDefaultModelName">The name of the new default propagation model</param>
	void SetDefaultModelName(const FName& NewDefaultModelName);

	UFUNCTION(BlueprintGetter)
	///<summary>Gets the array of frequency ranges used in this config</summary>
	///<returns>An array of frequency range structures</returns>
	TArray<FFrequencyRangeStruct> GetFrequenyRanges() const;

	UFUNCTION(BlueprintCallable)
	///<summary>Adds the frequency range to this config</summary>
	///<param name="FrequencyRange">The frequency range structure to add</param>
	void AddFrequencyRange(const FFrequencyRangeStruct& FrequencyRange);

	UFUNCTION(BlueprintCallable)
	///<summary>Removes a frequency range object from this config</summary>
	///<param name="FrequencyRange">A frequency range object with matching properties of the one to delete</param>
	///<bool>Whether an object was removed</bool>
	bool RemoveFrequencyRange(const FFrequencyRangeStruct& FrequencyRange);

private:
	UFUNCTION(BlueprintCallable)
	///<summary>Finds all child classes of USNRModel and populates the SNRModels array with them</summary>
	static void PopulateSNRModelsArray();

	UFUNCTION(BlueprintCallable)
	///<summary>Checks if a name is a valid SNR model class name</summary>
	///<param name="ModelName">The class name to check</param>
	///<returns>Whether it is valid</returns>
	static bool IsClassNameValidSNRModel(const FName& ModelName);

	UFUNCTION(BlueprintCallable)
	///<summary>Gets the UClass matching the model name if it is valid</summary>
	///<param name="ModelName">The name of the SNR model class to get</param>
	///<returns>The class of the SNR model or 
	static UClass* GetSNRModelClass(const FName& ModelName);

private:
	static TArray<TSubclassOf<USNRModel>> SNRModels;

	UPROPERTY(BlueprintGetter=GetDefaultModelName, BlueprintSetter=SetDefaultModelName)
	FName DefaultModelName;
	UPROPERTY(BlueprintGetter=GetFrequenyRanges)
	TArray<FFrequencyRangeStruct> FrequencyRanges;
};
