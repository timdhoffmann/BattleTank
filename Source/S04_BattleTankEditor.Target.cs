// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class S04_BattleTankEditorTarget : TargetRules
{
	public S04_BattleTankEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "S04_BattleTank" } );
	}
}
