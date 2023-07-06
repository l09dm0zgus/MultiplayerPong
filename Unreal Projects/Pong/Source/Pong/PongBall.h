// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PongBall.generated.h"


UCLASS()
class PONG_API APongBall : public AActor
{
	GENERATED_BODY()

public:	
	APongBall();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Speed{1000.0f};
	
	UFUNCTION(Reliable, Server, WithValidation, Category = "PongBall")
	void StartMoving();
	void StartMoving_Implementation();
	bool StartMoving_Validate();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
};
