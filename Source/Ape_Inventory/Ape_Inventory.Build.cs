// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ape_Inventory : ModuleRules
{
	public Ape_Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
