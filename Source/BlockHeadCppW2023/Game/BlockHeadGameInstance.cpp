// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UBlockHeadGameInstance::DebugCall() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("BlockHeadGameInstance Has Been Called"));
}

void UBlockHeadGameInstance::LoadNextLevel() {
	const int32 NextLevelIndex = CurrentLevelIndex + 1;

    UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(NextLevelIndex));
    UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(Levels.Num()));
    if (NextLevelIndex >= Levels.Num()){
        UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("No more levels to load. Current Level: %d", CurrentLevelIndex));
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("Loading Level", NextLevelIndex));
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[NextLevelIndex]);
    ++CurrentLevelIndex;
}

bool UBlockHeadGameInstance::isPlayerOnFinalLevel() const {
    return CurrentLevelIndex == Levels.Num()-1;
}

void UBlockHeadGameInstance::SetInputMode(bool GameOnly) const {
    const UWorld* World = GetWorld();
    if(!World) {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("Cannot access world"));
        return;
    }
    if(APlayerController* const Controller = World->GetFirstPlayerController()) {
	    if(!GameOnly) {
            const FInputModeGameOnly InputMode;
            Controller->SetInputMode(InputMode);
	    } else {
            const FInputModeUIOnly InputMode;
            Controller->SetInputMode(InputMode);
	    }

        Controller->bShowMouseCursor = !GameOnly;
    }
}

void UBlockHeadGameInstance::LoadFirstLevel() {
    CurrentLevelIndex = 0;
    Score = 0.0f;
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[CurrentLevelIndex]);
}

void UBlockHeadGameInstance::SaveScore(float ScoreToSave) {
    Score = ScoreToSave;
}

float UBlockHeadGameInstance::GetScore() {
    return Score;
}
