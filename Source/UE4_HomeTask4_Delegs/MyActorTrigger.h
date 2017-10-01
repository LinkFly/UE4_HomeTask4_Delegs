// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/GameFramework/GameModeBase.h"
#include "MyUE4_HomeTask4_DelegsGameMode.h"
#include "MyActorTrigger.generated.h"

UCLASS()
class UE4_HOMETASK4_DELEGS_API AMyActorTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorTrigger();

	UPROPERTY()
		UBoxComponent* TriggerBox;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AMyUE4_HomeTask4_DelegsGameMode* GetCurGameMode();
	
};
