// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class gojamk : ModuleRules
{
	public gojamk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","HAIPro","HStatsManager","AIModule","GameplayTasks","UMG" });
	}
}
