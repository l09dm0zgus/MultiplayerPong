// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "PongPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PongPlayer.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerStart.h"

APongGameModeBase::APongGameModeBase()
{
	DefaultPawnClass = APongPlayer::StaticClass();
	PlayerControllerClass  = APongPlayerController::StaticClass();
	bStartPlayersAsSpectators = true;
}

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}

AActor* APongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	Super::ChoosePlayerStart_Implementation(Player);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),Pawns);
	for(auto& Actor : Pawns)
	{
		auto PlayerStart = Cast<APlayerStart>(Actor);
		if(PlayerStart != nullptr)
		{
			if(PlayerStart->PlayerStartTag != TEXT("Taken"))
			{
				PlayerStart->PlayerStartTag = TEXT("Taken");
				return PlayerStart;
			}
		}
	}
	return nullptr;
}

void APongGameModeBase::GetPawns()
{
	
	Camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(),ACameraActor::StaticClass()));
	if(Camera == nullptr)
	{
		return;
	}
}

