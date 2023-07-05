// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerController.h"

void APongPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetPawn() != nullptr)
	{
		const FVector MoveDirection =  GetPawn()->ConsumeMovementInputVector();

		const FVector Movement = MoveDirection * Speed * DeltaTime;

		if (Movement.SizeSquared() > 0.0f)
		{
			FHitResult Hit(1.f);
			GetPawn()->GetRootComponent()->MoveComponent(Movement, GetPawn()->GetActorRotation(), true, &Hit);

			if (Hit.IsValidBlockingHit())
			{
				const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
				const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
				GetPawn()->GetRootComponent()->MoveComponent(Deflection, GetPawn()->GetActorRotation(), true);
			}
		}
	}

}

void APongPlayerController::Move(float Value)
{
	if (Value != 0.0f)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value);
	}
}
