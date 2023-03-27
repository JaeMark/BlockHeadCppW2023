// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockHeadGameInstance.h"

void UBlockHeadGameInstance::DebugCall() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("BlockHeadGameInstance Has Been Called"));
}
