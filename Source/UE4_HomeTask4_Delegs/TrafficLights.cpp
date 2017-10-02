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
	
	
}

// Called when the game starts or when spawned
void ATrafficLights::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World) {
		AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
		AMyUE4_HomeTask4_DelegsGameMode* GameMode = Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
		if (GameMode) {
			GameMode->TLSwitchDel.BindUObject(this, &ATrafficLights::OnSwitchColor);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Error!!! Failed gettings game mode"));
		}
	}
	
	
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

UPointLightComponent * ATrafficLights::GetColorComponent(ETrafficLightsColors Color)
{
	switch (Color) {
	case Red:
		return LightRed;
		break;
	case Yellow:
		return LightYellow;
		break;
	case Green:
		return LightGreen;
		break;
	}
	return nullptr;
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

void ATrafficLights::SwitchColor(ETrafficLightsColors Color) {
	CurColor = Color;
	HideLights();
	UPointLightComponent* Light = GetColorComponent(Color);
	Light->SetVisibility(true);
}

void ATrafficLights::SwitchRoadTrigger(ERoadOpenOrClose OpenOrClose)
{
	AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
	AMyUE4_HomeTask4_DelegsGameMode* GameMode = Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
	if (GameMode) {
		GameMode->OnRoadFree.Broadcast(OpenOrClose);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Error: Bad GameMode"));
	}
}

void ATrafficLights::StartWork()
{
	SwitchColor(NextColor);
	switch (CurColor) {
	case Green:
		SwitchRoadTrigger(RoadOpen);
		break;
	case Yellow:
		NextColor = Green;
		StartWorkByTimer();
		break;
	
	case Red:
		SwitchRoadTrigger(RoadClose);
		NextColor = Yellow;
		StartWorkByTimer();
		break;
	}
}

void ATrafficLights::OnSwitchColor(ETrafficLightsColors ColorType)
{
	NextColor = ColorType;
	StartWork();
}