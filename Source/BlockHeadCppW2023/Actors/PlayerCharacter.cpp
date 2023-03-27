// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Obstacle.h"
#include "EndPoint.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// Let designers be responsible for these
	//SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
	//SprintArm->TargetArmLength = 400.0f;
	//SpringArm->bInheritPitch;
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
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
	/*
	if (Cube) {
		Cube->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	}
	*/
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!bLevelEnded) {
		const FVector CubeForce = FVector(ForwardForce, 0.0f, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}

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
	const float MovementAxis = Value.Get<float>();

	if(!bLevelEnded) {
		const FVector CubeForce = FVector(0.0f, MovementAxis * SideForce, 0.0f);
		Cube->AddForce(CubeForce, NAME_None, true);
	}
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit) {
	if(OtherActor && OtherActor->IsA(AObstacle::StaticClass())) {
		GLUTTON_LOG("ON HIT: OBSTACLE");
		//bLevelEnded = true;
		//Cube->SetPhysicsLinearVelocity({ 0, 0, 0 });
	}
}
void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(AEndPoint::StaticClass())) {
		GLUTTON_LOG("ON OVERLAP");
		//bLevelEnded = true;
	}
}

