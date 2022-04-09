// Shoot Them Up Game. All Right Reserved 2022.

using UnrealBuildTool;
using System.Collections.Generic;

public class ST_ShootThemUpTarget : TargetRules
{
	public ST_ShootThemUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ST_ShootThemUp" } );
	}
}
