// Halloween Nightmare. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HalloweenNightmareEditorTarget : TargetRules
{
	public HalloweenNightmareEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("HalloweenNightmare");
	}
}
