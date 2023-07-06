// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	ProjectileMovement->MaxSpeed = Speed * 10.0f;
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
	
}


