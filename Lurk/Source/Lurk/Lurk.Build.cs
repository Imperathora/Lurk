// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lurk : ModuleRules
{
	public Lurk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
