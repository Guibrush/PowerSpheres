// Copyright 2019-2020 Alberto & co. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class PowerSpheresServerTarget : TargetRules
{
	public PowerSpheresServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		ExtraModuleNames.Add("PowerSpheres");
		bUsesSteam = true;
	}
}