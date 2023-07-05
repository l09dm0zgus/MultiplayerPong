// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "PongPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PongPlayer.h"
#include "Camera/CameraActor.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APongGameModeBase::APongGameModeBase()
{
	DefaultPawnClass = APongPlayer::StaticClass();
	PlayerControllerClass  = APongPlayerController::StaticClass();
	bStartPlayersAsSpectators = true;
	Players.Init(nullptr,2);
}

void APongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if(Players[0] == nullptr || Players[1] == nullptr)
	{
		GetPawns();
	}
	
	auto Player = Cast<APongPlayer>(Players[GetNumPlayers() - 1]);
	NewPlayer->Possess(Player);
}

void APongGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (GetNumPlayers() > 2)
	{
		ErrorMessage = "Player Rejected: Game Full";
	}
}

AActor* APongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	Super::ChoosePlayerStart_Implementation(Player);
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),Actors);
	for(auto& Actor : Actors)
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
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APongPlayer::StaticClass(),Actors);
	
	if(Actors.Num() > 1)
	{
		Players[0] = Cast<APongPlayer>(Actors[0]);
		Players[1] = Cast<APongPlayer>(Actors[1]);
	}
	
}

