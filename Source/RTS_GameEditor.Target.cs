// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class RTS_GameEditorTarget : TargetRules
{
	public RTS_GameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RTS_Game" } );
		
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
	}
}
