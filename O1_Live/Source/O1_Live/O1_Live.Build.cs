// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class O1_Live : ModuleRules
{
	public O1_Live(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
            { "Core",
            "CoreUObject",
            "Engine",
            "InputCore" ,
            "EnhancedInput",
            "NavigationSystem",
            "AIModule",
            "GameplayTasks",
            "UMG",});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[]
        {
            "O1_Live"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
