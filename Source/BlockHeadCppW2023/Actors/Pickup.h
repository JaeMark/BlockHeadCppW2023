// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

// FORWARD DECLARATIONS
class ABlockHeadGameMode;
class USphereComponent;
class UNiagaraComponent;

UCLASS()
class BLOCKHEADCPPW2023_API APickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APickup();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float PickupValue = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        FLinearColor PickupColor = FLinearColor::Yellow;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Setup")
        UStaticMeshComponent* PickupMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Setup")
        USphereComponent* PickupRange;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Setup")
        UNiagaraComponent* NiagaraSystem;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        USceneComponent* Root;

    // POINTERS
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        ABlockHeadGameMode* GameModeRef;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
        void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintImplementableEvent)
        void UpdateScore(float DeltaScore) const;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};