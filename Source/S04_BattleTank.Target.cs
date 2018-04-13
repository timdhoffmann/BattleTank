// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class S04_BattleTankTarget : TargetRules
{
	public S04_BattleTankTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "S04_BattleTank" } );
	}
}
