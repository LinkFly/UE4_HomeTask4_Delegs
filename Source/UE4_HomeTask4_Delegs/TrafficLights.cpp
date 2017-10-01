// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficLights.h"


// Sets default values
ATrafficLights::ATrafficLights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	ConstructorHelpers::FObjectFinder<UStaticMesh> TrafficLightsMesh(TEXT("StaticMesh'/Game/Developers/Asus/SM_Traffic_Light.SM_Traffic_Light'"));
	ConstructorHelpers::FObjectFinder<UMaterial> MaterialLights(TEXT("Material'/Game/ExampleContent/Materials/ExampleAsset/MaterialLayers/M_Metal_UsingMF.M_Metal_UsingMF'"));
	if (TrafficLightsMesh.Object) {
		StaticMesh->SetStaticMesh(TrafficLightsMesh.Object);
		if (MaterialLights.Object) {
			StaticMesh->SetMaterial(LightElementsIndex, MaterialLights.Object);
		}
	}
	LightRed = CreateDefaultSubobject<UPointLightComponent>("Red");
	LightYellow = CreateDefaultSubobject<UPointLightComponent>("Yellow");
	LightGreen = CreateDefaultSubobject<UPointLightComponent>("Green");
	InitLight(LightRed, FLinearColor(1, 0, 0, 1), FVector(0.5f, 18, 175));
	InitLight(LightYellow, FLinearColor(1, 1, 0, 1), FVector(0.5f, 18, 158));
	InitLight(LightGreen, FLinearColor(0, 1, 0, 1), FVector(0.5f, 18, 141));

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("TrafficLightsScene");
	StaticMesh->SetupAttachment(SceneRoot);
	LightRed->SetupAttachment(SceneRoot);
	LightYellow->SetupAttachment(SceneRoot);
	LightGreen->SetupAttachment(SceneRoot);
	SceneRoot->SetRelativeScale3D(FVector(2, 2, 2));
	RootComponent = SceneRoot;
	
	/*
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("TrafficLightsScene");
	LightRed->SetupAttachment(SceneRoot);
	LightYellow->SetupAttachment(SceneRoot);
	LightGreen->SetupAttachment(SceneRoot);
	StaticMesh->SetupAttachment(SceneRoot);
	RootComponent = SceneRoot;*/
}

// Called when the game starts or when spawned
void ATrafficLights::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
	AMyUE4_HomeTask4_DelegsGameMode* GameMode = Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
	GameMode->TLSwitchDel.BindUObject(this, &ATrafficLights::SwitchColor);

}

// Called every frame
void ATrafficLights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrafficLights::InitLight(UPointLightComponent *& Light, FLinearColor Color, FVector Location)
{
	Light->SetVisibility(false);
	Light->SetLightColor(FLinearColor(Color));
	Light->SetRelativeLocation(Location);
}

void ATrafficLights::HideLights()
{
	LightRed->SetVisibility(false);
	LightYellow->SetVisibility(false);
	LightGreen->SetVisibility(false);
}

void ATrafficLights::StartWorkByTimer() {
	GetWorldTimerManager().SetTimer(Timer, this, &ATrafficLights::StartWork, SwitchTime, false);
}

void ATrafficLights::SwitchColor(ETrafficLightsColors ColorType)
{
	CurColor = ColorType;
	switch (ColorType) {
	case Red: EnableRed(); break;
	case Yellow: EnableYellow(); break;
	case Green: EnableGreen(); break;
	}
	StartWorkByTimer();
}

void ATrafficLights::StartWork()
{
	switch (CurColor) {
	case Red:
		SwitchColor(Yellow);
		StartWorkByTimer();
		break;
	case Yellow:
		SwitchColor(Green);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Already Green - signal event!"));
		//AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
		//AMyUE4_HomeTask4_DelegsGameMode* GameMode = Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
		//if (GameMode) {
		//	//GameMode->RoadFreeEvt.Broadcast();
		//}
		//else {
		//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Error: Bad GameMode"));
		//}
		OnRoadFree.Broadcast();
		break;
	//case Green:
	//	// Stub for future
	//	break;
	}
	
}

void ATrafficLights::EnableRed()
{
	HideLights();
	LightRed->SetVisibility(true);
}

void ATrafficLights::EnableYellow()
{
	HideLights();
	LightYellow->SetVisibility(true);
}

void ATrafficLights::EnableGreen()
{
	HideLights();
	LightGreen->SetVisibility(true);
}