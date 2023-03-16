// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"


using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

#define GLUTTON_LOG(Message) \
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(Message)); \
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, Message)
#define PRINTF(Message, Variable) FString::Printf(TEXT(Message), Variable)

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Hello from C++ Player Character Constructor"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if(PlayerController) {
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer);
		if(SubSystem) {
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	int32 Answer = 42;
	float Pi = 3.14;
	FString Msg{ "This is a message" };

	GLUTTON_LOG("Hello from C++ Player Character BeginPlay.");
	GLUTTON_LOG(PRINTF("Hello Logging float: %f", Pi));

	/*


	UE_LOG(LogTemp, Warning, TEXT("Hello from C++ Player Character BeginPlay"));
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging int: %d"), Answer);
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging float: %f"), Pi);
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging FString: %s"), *Msg);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("On Screen Hello from C++ Player Character BeginPlay"));
	*/
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEIC* EnchancedInputComponent = CastChecked<UEIC>(PlayerInputComponent);
	if(EnchancedInputComponent) {
		EnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHorizontally);
	}
}

void APlayerCharacter::MoveHorizontally(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Warning, TEXT("Hello Logging float: %f"), 0);
}

