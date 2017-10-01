// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActorTrigger.h"


// Sets default values
AMyActorTrigger::AMyActorTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
}

// Called when the game starts or when spawned
void AMyActorTrigger::BeginPlay()
{
	Super::BeginPlay();

}

//void AMyActorTrigger::Start() {
//
//}

void AMyActorTrigger::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AMyUE4_HomeTask4_DelegsGameMode* GameMode = GetCurGameMode();
	if (GameMode) {
		GameMode->TLSwitchDel.ExecuteIfBound(Red);

	}
}

// Called every frame
void AMyActorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AMyUE4_HomeTask4_DelegsGameMode* AMyActorTrigger::GetCurGameMode() {
	AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
	return Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
}