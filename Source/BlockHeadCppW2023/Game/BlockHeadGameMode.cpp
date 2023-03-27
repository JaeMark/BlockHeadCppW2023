// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameMode.h"

void ABlockHeadGameMode::DebugCall() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("BlockHeadGameMode Has Been Called"));
}
