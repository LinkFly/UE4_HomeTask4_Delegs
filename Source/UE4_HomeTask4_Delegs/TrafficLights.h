// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GameStructs.h"
#include "MyUE4_HomeTask4_DelegsGameMode.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "TrafficLights.generated.h"

DECLARE_EVENT(UObstacle, FRoadFreeEvent)

UCLASS()
class UE4_HOMETASK4_DELEGS_API ATrafficLights : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrafficLights();

	FRoadFreeEvent OnRoadFree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPointLightComponent* LightRed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPointLightComponent* LightYellow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPointLightComponent* LightGreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SwitchTime = 3.0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SwitchColor(ETrafficLightsColors ColorType);

	UFUNCTION()
		void HideLights();

	UFUNCTION(BlueprintCallable)
		void EnableRed();

	UFUNCTION(BlueprintCallable)
		void EnableYellow();

	UFUNCTION(BlueprintCallable)
		void EnableGreen();

	UFUNCTION(BlueprintCallable)
	void StartWork();

private:
	const int LightElementsIndex = 1;
	void InitLight(UPointLightComponent* &Light, FLinearColor Color, FVector Location);
	void StartWorkByTimer();
	ETrafficLightsColors CurColor = Red;
};
