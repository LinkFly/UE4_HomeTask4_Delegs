// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle");
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mesh.Object) {
		StaticMesh->SetStaticMesh(Mesh.Object);
	}
	StaticMesh->SetRelativeScale3D(FVector(10, 1, 10));
	///////////////

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	AGameModeBase* CurGameMode = GetWorld()->GetAuthGameMode();
	AMyUE4_HomeTask4_DelegsGameMode* GameMode = Cast<AMyUE4_HomeTask4_DelegsGameMode>(CurGameMode);
	if (GameMode) {
		GameMode->OnRoadFree.AddUObject(this, &AObstacle::OpenOrClose);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Error: Bad GameMode"));
	}
}

void AObstacle::Open()
{
	IsClosing = false;
	IsOpening = true;
}

void AObstacle::Close()
{
	IsOpening = false;
	IsClosing = true;
}

void AObstacle::OpenOrClose(ERoadOpenOrClose OpenOrClose)
{
	if (OpenOrClose == RoadOpen) Open();
	if (OpenOrClose == RoadClose) Close();
}

void AObstacle::CheckCurPosition()
{
	float curZ = GetActorLocation().Z;
	if (curZ < ZMin) {
		IsOpening = false;
	}
	if (curZ > ZMax) {
		IsClosing = false;
	}
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpening || IsClosing) {
		float zDiff = OpenSpeed * DeltaTime;
		if (IsOpening) {
			zDiff *= -1;
		}
		SetActorLocation(GetActorLocation() + FVector(0, 0, zDiff));
		CheckCurPosition();
	}
}
