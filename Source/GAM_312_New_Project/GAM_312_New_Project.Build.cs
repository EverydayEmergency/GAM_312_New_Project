// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM_312_New_Project : ModuleRules
{
	public GAM_312_New_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
