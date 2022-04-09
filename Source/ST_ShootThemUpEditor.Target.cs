// Shoot Them Up Game. All Right Reserved 2022.

using UnrealBuildTool;
using System.Collections.Generic;

public class ST_ShootThemUpEditorTarget : TargetRules
{
	public ST_ShootThemUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ST_ShootThemUp" } );
	}
}
