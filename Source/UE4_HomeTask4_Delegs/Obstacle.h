// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "MyUE4_HomeTask4_DelegsGameMode.h"
#include "TrafficLights.h"
#include "GameStructs.h"
#include "Obstacle.generated.h"

UCLASS()
class UE4_HOMETASK4_DELEGS_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY()
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsOpening = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsClosing = false;

	UFUNCTION()
		void Open();
	UFUNCTION()
		void Close();
	UFUNCTION()
		void OpenOrClose(ERoadOpenOrClose OpenOrClose);

	void CheckCurPosition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 OpenSpeed = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZMin = -500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZMax = 500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
