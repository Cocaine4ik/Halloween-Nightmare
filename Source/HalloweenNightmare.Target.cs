// Halloween Nightmare. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HalloweenNightmareTarget : TargetRules
{
	public HalloweenNightmareTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("HalloweenNightmare");
	}
}
