// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FVehicleTestbedTestsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	///<summary>This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module</summary>
	virtual void StartupModule() override;

	///<summary>This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading, we call this function before unloading the module.</summary>
	virtual void ShutdownModule() override;
};
