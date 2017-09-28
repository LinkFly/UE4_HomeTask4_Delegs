// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4_HomeTask4_DelegsEditorTarget : TargetRules
{
	public UE4_HomeTask4_DelegsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("UE4_HomeTask4_Delegs");
	}
}
