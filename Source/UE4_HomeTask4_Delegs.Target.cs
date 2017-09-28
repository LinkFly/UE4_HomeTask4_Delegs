// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4_HomeTask4_DelegsTarget : TargetRules
{
	public UE4_HomeTask4_DelegsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("UE4_HomeTask4_Delegs");
	}
}
