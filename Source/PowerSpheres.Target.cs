// Copyright 2019-2020 Alberto & co. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PowerSpheresTarget : TargetRules
{
	public PowerSpheresTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("PowerSpheres");
	}
}
