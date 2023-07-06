// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"

#include "BallSpawnPosition.h"
#include "PongGameModeBase.h"
#include "PongPlayer.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	UStaticMesh* SphereMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")).Object;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(SphereMesh);
	
	RootComponent = Mesh;
	
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 5.0f;
}


void APongBall::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &APongBall::OnHit);
	SetReplicateMovement(true);
}

void APongBall::StartMoving_Implementation()
{
	const auto RandomInitialDirection = UKismetMathLibrary::RandomBool();
	const auto MovementDirectionAfterSpawn = FVector( 0.0, 0.0,RandomInitialDirection ? 1.0 : -1.0);
	Mesh->SetPhysicsLinearVelocity(MovementDirectionAfterSpawn * Speed);
}

bool APongBall::StartMoving_Validate()
{
	return true;
}

void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->Tags.Num() > 0 && OtherActor->Tags[0] != FName(TEXT("P2")) &&  OtherActor->Tags[0] != FName(TEXT("P1")))
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),APongPlayer::StaticClass(),Actors);
		
		if(OtherActor->Tags[0] == FName(TEXT("P1Gate")))
		{
			auto it = Actors.FindByPredicate([](const AActor *Actor)
			{
				return Actor->Tags.Num() != 0 && Actor->Tags[0] == FName(TEXT("P2"));
			});

			if(it != nullptr)
			{
				auto Player = Cast<APongPlayer>(*it);
				
				if(Player != nullptr)
				{
					auto CurrentScore = Player->GetPlayerState()->GetScore();
					CurrentScore++;
					Player->GetPlayerState()->SetScore(CurrentScore);
				}
			}
			
		
		}
		if(OtherActor->Tags[0] == FName(TEXT("P2Gate")))
		{
			auto *it = Actors.FindByPredicate([](const AActor *Actor)
			{
				return Actor->Tags.Num() != 0 && Actor->Tags[0] == FName(TEXT("P1"));
			});

			if(it != nullptr)
			{
				auto Player = Cast<APongPlayer>(*it);
			
				if(Player != nullptr)
				{
					auto CurrentScore = Player->GetPlayerState()->GetScore();
					CurrentScore++;
					Player->GetPlayerState()->SetScore(CurrentScore);
				}
			}
			
		}
		
		auto BallSpawner = Cast<ABallSpawnPosition>(UGameplayStatics::GetActorOfClass(GetWorld(),ABallSpawnPosition::StaticClass()));
		if(BallSpawner != nullptr)
		{
			if(Destroy())
			{
				BallSpawner->SpawnBall();
			}
		}
	}
}


