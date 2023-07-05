// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "PongPlayerController.h"
// Sets default values
APongPlayer::APongPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetBoxExtent({32.0f,180.0f,32.0f});
	
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	if(CubeMesh != nullptr)
	{
		Mesh->SetStaticMesh(CubeMesh);
	}

	RootComponent = BoxComponent;
	Mesh->SetRelativeScale3D(FVector(0.6, 3.5, 0.4));
	Mesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent->SetIsReplicated(true);
	Mesh->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void APongPlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APongPlayerController>(GetController());
	
}

// Called every frame
void APongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"),PlayerController,&APongPlayerController::Move);
}

