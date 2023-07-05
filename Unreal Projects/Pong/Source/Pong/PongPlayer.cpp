// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "PongPlayerController.h"

APongPlayer::APongPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	SetReplicatingMovement(true);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	if(CubeMesh != nullptr)
	{
		Mesh->SetStaticMesh(CubeMesh);
	}
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetBoxExtent({32.0f,180.0f,32.0f});
	RootComponent = BoxComponent;
	
	Mesh->SetRelativeScale3D(FVector(0.6, 3.5, 0.4));
	Mesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
}


void APongPlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APongPlayerController>(GetController());
}

void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"),PlayerController,&APongPlayerController::Move);
}

