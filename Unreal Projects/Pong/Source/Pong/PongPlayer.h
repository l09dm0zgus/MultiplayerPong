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
	// Sets default values for this pawn's properties
	APongPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent *BoxComponent;

	class APongPlayerController *PlayerController;

	
};
