// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPlayer.generated.h"

class UBoxComponent;
class UPlayerMovementComponent;

UCLASS()
class PONG_API APongPlayer : public APawn
{
	GENERATED_BODY()

public:
	APongPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent *BoxComponent;

	class APongPlayerController *PlayerController;

	

};
