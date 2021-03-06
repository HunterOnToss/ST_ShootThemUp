// Shoot Them Up Game. All Right Reserved 2022.

using UnrealBuildTool;

public class ST_ShootThemUp : ModuleRules
{
	public ST_ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" ,
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"ST_ShootThemUp/Public/Player", 
			"ST_ShootThemUp/Public/Components", 
			"ST_ShootThemUp/Public/Dev",
			"ST_ShootThemUp/Public/Weapon",
			"ST_ShootThemUp/Public/Weapon/Components",
			"ST_ShootThemUp/Public/UI",
			"ST_ShootThemUp/Public/Animation",
			"ST_ShootThemUp/Public/AI",
			"ST_ShootThemUp/Public/AI/Tasks",
			"ST_ShootThemUp/Public/AI/Services",
			"ST_ShootThemUp/Public/AI/EQS",
			"ST_ShootThemUp/Public/AI/Decorator",
			"ST_ShootThemUp/Public/Menu",
			"ST_ShootThemUp/Public/Menu/UI"


		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
