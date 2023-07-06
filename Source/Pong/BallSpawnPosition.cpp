// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawnPosition.h"
#include "PongBall.h"
#include "Components/SceneComponent.h"

ABallSpawnPosition::ABallSpawnPosition()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;
}

void ABallSpawnPosition::SpawnBall()
{
	auto Ball = GetWorld()->SpawnActor<APongBall>(APongBall::StaticClass(),GetActorLocation(),{0.0f,90.0f,0.0});
	Ball->SetOwner(this);
}

void ABallSpawnPosition::BeginPlay()
{
	Super::BeginPlay();
	
}


