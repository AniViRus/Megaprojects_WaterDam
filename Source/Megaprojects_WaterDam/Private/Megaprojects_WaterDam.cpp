// Copyright Epic Games, Inc. All Rights Reserved.

#include "Megaprojects_WaterDam.h"

#define LOCTEXT_NAMESPACE "FMegaprojects_WaterDamModule"

void FMegaprojects_WaterDamModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMegaprojects_WaterDamModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMegaprojects_WaterDamModule, Megaprojects_WaterDam)