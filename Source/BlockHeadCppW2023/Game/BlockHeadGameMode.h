// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockHeadGameMode.generated.h"

// FORWARD DECLARATIONS
class UBlockHeadGameInstance;

UCLASS()
class BLOCKHEADCPPW2023_API ABlockHeadGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FTimerHandle LevelSwapTimer;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DebugCall();
	void LevelCompleted();
	void NextLevel();
	void GameCompleted(bool PlayerWon);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBlockHeadGameInstance* GameInstanceRef;
};
