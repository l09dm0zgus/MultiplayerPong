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
	RootComponent = Mesh;
	Mesh->SetStaticMesh(SphereMesh);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->BounceVelocityStopSimulatingThreshold = 0.01f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
}


void APongBall::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->OnComponentHit.AddDynamic(this, &APongBall::OnHit);
	SetReplicateMovement(true);
}

void APongBall::StartMoving_Implementation()
{
	auto RandomInitialDirection = UKismetMathLibrary::RandomBool();
	auto MovementDirectionAfterSpawn = FVector(RandomInitialDirection ? 1.0 : -1.0, 0.0, 0.0);
	Mesh->SetPhysicsLinearVelocity(MovementDirectionAfterSpawn * Speed);
}

bool APongBall::StartMoving_Validate()
{
	return true;
}

void APongBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
}


