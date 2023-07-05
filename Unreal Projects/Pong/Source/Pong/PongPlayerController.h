// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	
	UPROPERTY(EditAnywhere)
	float Speed{600};
public:
	void Tick(float DeltaTime) override;
	void Move(float Value);
	
};
