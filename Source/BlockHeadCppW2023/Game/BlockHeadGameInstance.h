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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> LevelNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSoftObjectPtr<UWorld>> ProperLevels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 CurrentLevelIndex = 1;
};
