// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockHeadGameMode.generated.h"

// FORWARD DECLARATIONS
class UBlockHeadGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateScore, float, NewScore);

UCLASS()
class BLOCKHEADCPPW2023_API ABlockHeadGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FTimerHandle LevelSwapTimer;

	UPROPERTY(BlueprintReadOnly)
		UBlockHeadGameInstance* GameInstanceRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;

	UPROPERTY()
		UUserWidget* LevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<UUserWidget> DefaultGameCompleteWidget;

	UPROPERTY()
		UUserWidget* GameCompleteWidget;

	UPROPERTY()
		UUserWidget* ScoreWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<UUserWidget> DefaultScoreWidget;

	UPROPERTY()
		float CurrentScore = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnUpdateScore OnUpdateScore;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DebugCall();
	void LevelCompleted();
	void NextLevel();
	void GameCompleted(bool PlayerWon);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void UpdateScore(float DeltaScore);
		virtual void UpdateScore_Implementation(float DeltaScore);
};
