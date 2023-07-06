// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallSpawnPosition.generated.h"

UCLASS()
class PONG_API ABallSpawnPosition : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallSpawnPosition();
	void SpawnBall();
protected:
	virtual void BeginPlay() override;
	
private:
	class USceneComponent *SceneComponent;
};
