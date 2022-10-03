// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EduProject : ModuleRules
{
	public EduProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
