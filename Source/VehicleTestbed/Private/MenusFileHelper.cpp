// Fill out your copyright notice in the Description page of Project Settings.

#include "MenusFileHelper.h"
#include "Core.h"

TArray<FString> UMenusFileHelper::FileNames(FString directory)
{
	TArray<FString> result;

	result.Empty();

	IFileManager::Get().FindFiles(result, *directory, true, false);

	return result;
}

UFUNCTION(BlueprintPure, Category = "My Functions")
TArray<FString> UMenusFileHelper::MapNames()
{
	return FileNames("./Content/Maps");
}
