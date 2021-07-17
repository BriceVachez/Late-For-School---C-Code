// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_test_5 : ModuleRules
{
	public FPS_test_5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
	}
}
