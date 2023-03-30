// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlockHeadGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKHEADCPPW2023_API UBlockHeadGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Levels")
		int32 CurrentLevelIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Levels")
		TArray<TSoftObjectPtr<UWorld>> Levels;;

public:
	void DebugCall();
	void LoadNextLevel();
	bool isPlayerOnFinalLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
		void SetInputMode(bool GameOnly) const;
	// Get the world
	// From the World, get the first player controller. (APlayerController*)
	// Call set input mode on controller with one of two structs:
	//	-const FInputModeGameOnly InputMode;
	//	-const FInputModeUIOnly InputMode;
	// Controller->bShowMouseCursor (UI mode true, Game mode false);


	UFUNCTION(BlueprintCallable, Category = "Game Levels")
		void LoadFirstLevel();
};
