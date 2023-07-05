// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawnPosition.h"
#include "Components/SceneComponent.h"

ABallSpawnPosition::ABallSpawnPosition()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;
}

void ABallSpawnPosition::BeginPlay()
{
	Super::BeginPlay();
	
}


