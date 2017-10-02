// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE4_HomeTask4_DelegsGameMode.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "MyUE4_HomeTask4_DelegsGameMode.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FTLightsSwitchDelegate, ETrafficLightsColors)
DECLARE_EVENT_OneParam(AMyUE4_HomeTask4_DelegsGameMode, FRoadFreeEvent, ERoadOpenOrClose)

UCLASS()
class UE4_HOMETASK4_DELEGS_API AMyUE4_HomeTask4_DelegsGameMode : public AUE4_HomeTask4_DelegsGameMode
{
	GENERATED_BODY()

public:
	FTLightsSwitchDelegate TLSwitchDel;
	FRoadFreeEvent OnRoadFree;
};
