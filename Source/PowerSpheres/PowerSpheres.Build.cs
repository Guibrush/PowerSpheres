// Copyright 2019-2020 Alberto & co. All Rights Reserved.

using UnrealBuildTool;

public class PowerSpheres : ModuleRules
{
	public PowerSpheres(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "GameplayAbilities", "GameplayTasks", "UMG" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "MinimapPlugin" });
    }
}
