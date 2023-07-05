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
	UFUNCTION(Reliable, Server, WithValidation, Category = "PongStickPawn")
	void MoveLaterally(float Value);
	void MoveLaterally_Implementation(float Value);
	bool MoveLaterally_Validate(float Value);
	
	UPROPERTY(EditAnywhere)
	float Speed{600};

public:
	APongPlayerController();
	void Tick(float DeltaTime) override;
	void Move(float Value);
	
};
