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
	auto Ball = GetWorld()->SpawnActor<APongBall>(APongBall::StaticClass(),GetActorLocation(),FRotator::ZeroRotator);
	Ball->SetOwner(this);
}

void ABallSpawnPosition::BeginPlay()
{
	Super::BeginPlay();
	
}


