// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"

#include "TimerManager.h"
#include "BlockHeadCppW2023/Game/BlockHeadGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ABlockHeadGameMode::BeginPlay() {
	GameInstanceRef = Cast<UBlockHeadGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstanceRef) {
		GameInstanceRef->LoadNextLevel();
	}
}

void ABlockHeadGameMode::DebugCall() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("BlockHeadGameMode Has Been Called"));
}

void ABlockHeadGameMode::LevelCompleted() {
	GameInstanceRef->DebugCall();
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABlockHeadGameMode::NextLevel, 2.0f, false);
}

void ABlockHeadGameMode::NextLevel() {
	GameInstanceRef->LoadNextLevel();
}

void ABlockHeadGameMode::GameCompleted(bool PlayerWon) {
}
