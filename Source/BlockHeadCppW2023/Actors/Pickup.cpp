// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "PlayerCharacter.h"
#include "BlockHeadCppW2023/Game/BlockHeadGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRange"));
	RootComponent = PickupRange;

	// Set the default sphere radius
	PickupRange->SetSphereRadius(60.0f);

	if (PickupRange) {
		PickupRange->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
	}

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetCollisionProfileName(TEXT("NoCollision"));
	PickupMesh->SetupAttachment(PickupRange);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Scored A Point"));
		UpdateScore(PickupValue);
		Destroy();
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

