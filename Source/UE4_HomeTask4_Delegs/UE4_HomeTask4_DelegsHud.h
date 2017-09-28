// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "UE4_HomeTask4_DelegsHud.generated.h"


UCLASS(config = Game)
class AUE4_HomeTask4_DelegsHud : public AHUD
{
	GENERATED_BODY()

public:
	AUE4_HomeTask4_DelegsHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
