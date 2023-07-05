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
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
private:
	TArray<AActor*> Pawns;
	ACameraActor *Camera;
	void GetPawns();
};
