// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UE4_HomeTask4_DelegsGameMode.h"
#include "UE4_HomeTask4_DelegsPawn.h"
#include "UE4_HomeTask4_DelegsHud.h"

AUE4_HomeTask4_DelegsGameMode::AUE4_HomeTask4_DelegsGameMode()
{
	DefaultPawnClass = AUE4_HomeTask4_DelegsPawn::StaticClass();
	HUDClass = AUE4_HomeTask4_DelegsHud::StaticClass();
}
