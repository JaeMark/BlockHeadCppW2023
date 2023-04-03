// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"

#include "TimerManager.h"
#include "BlockHeadCppW2023/Game/BlockHeadGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ABlockHeadGameMode::BeginPlay() {
	GameInstanceRef = Cast<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ABlockHeadGameMode::DebugCall() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("BlockHeadGameMode Has Been Called"));
}

void ABlockHeadGameMode::LevelCompleted() {
	if(DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		LevelCompleteWidget->AddToViewport();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultLevelCompleteWidget has not been set."));
	}

	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABlockHeadGameMode::NextLevel, 2.0f, false);
}

void ABlockHeadGameMode::NextLevel() {
	if(GameInstanceRef->isPlayerOnFinalLevel()) {
		if(LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromParent();
		}
		GameCompleted(true);
	} else {
		GameInstanceRef->LoadNextLevel();
	}
}

void ABlockHeadGameMode::GameCompleted(bool PlayerWon) {
	// set input mode to UI only
	GameInstanceRef->SetInputMode(false);

	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
			UTextBlock* LostOrComplete = Cast<UTextBlock>(
				GameCompleteWidget->GetWidgetFromName(TEXT("LostOrComplete"))
			);
			if(LostOrComplete) {
				const FText WinLossMessage = PlayerWon ? FText::FromString("You Won!") : FText::FromString("You Lost!");
				LostOrComplete->SetText(WinLossMessage);
			}
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultGameCompleteWidget has not been set."));
	}
}
