// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APongGameModeBase();
	
protected:
	virtual void PostLogin(APlayerController * NewPlayer) override;
	virtual void PreLogin(const FString & Options,const FString & Address,const FUniqueNetIdRepl & UniqueId,FString & ErrorMessage) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	void BeginPlay() override;
private:
	TArray<class APongPlayer*> Players;
	int32 NumberOfPlayers{0};
	void GetActors();
	
	
	UPROPERTY(VisibleAnywhere)
	class ABallSpawnPosition *BallSpawnPosition{nullptr};

	
};
