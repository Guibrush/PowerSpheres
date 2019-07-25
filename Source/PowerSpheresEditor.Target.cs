// Copyright 2019-2020 Alberto & co. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PowerSpheresEditorTarget : TargetRules
{
	public PowerSpheresEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.Add("PowerSpheres");
	}
}
