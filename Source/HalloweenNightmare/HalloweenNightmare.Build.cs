// Halloween Nightmare. All Rights Reserved.

using UnrealBuildTool;

public class HalloweenNightmare : ModuleRules
{
	public HalloweenNightmare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		PublicIncludePaths.AddRange(new[]
		{
		"HalloweenNightmare/Public/Player",
		"HalloweenNightmare/Public/UI",
		"HalloweenNightmare/Public/Environment",
		"HalloweenNightmare/Public/Pickups"
		});
	}
}