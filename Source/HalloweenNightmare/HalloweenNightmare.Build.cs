// Halloween Nightmare. All Rights Reserved.

using UnrealBuildTool;

public class HalloweenNightmare : ModuleRules
{
	public HalloweenNightmare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "SlateCore"});
		PublicIncludePaths.AddRange(new[]
		{
		"HalloweenNightmare/Public/Player",
		"HalloweenNightmare/Public/UI",
		"HalloweenNightmare/Public/Levels",
		"HalloweenNightmare/Public/Pickups",
		"HalloweenNightmare/Public/Menu"
		});
	}
}