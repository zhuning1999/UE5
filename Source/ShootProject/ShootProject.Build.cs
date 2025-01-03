// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootProject : ModuleRules
{
	public ShootProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
