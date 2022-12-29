// Fill out your copyright notice in the Description page of Project Settings.


#include "DiggerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Attack.h"
#include "Components/SpotLightComponent.h"





// Sets default values
ADiggerCharacter::ADiggerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComp->SetupAttachment(RootComponent);
	SpotLight = CreateDefaultSubobject<USpotLightComponent>("SpotLight");
	SpotLight->SetupAttachment(FlipbookComp);
}

// Called when the game starts or when spawned
void ADiggerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ADiggerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckSpriteRotation();
	CheckSpriteJump();
}

// Called to bind functionality to input
void ADiggerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ADiggerCharacter::MoveRight);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	Input->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADiggerCharacter::Attack);
	Input->BindAction(DigAction, ETriggerEvent::Triggered, this, &ADiggerCharacter::Dig);

}


void ADiggerCharacter::MoveRight(const FInputActionInstance& Instance) {
	if (State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE)) return;
	float FloatValue = Instance.GetValue().Get<float>();
	AddMovementInput(GetActorRightVector() * FloatValue);
	if (FloatValue > 0) {
		FlipbookComp->SetRelativeRotation(FRotator(0,90,0));
		FVector LightRightSide = FVector(2,1,6);
		SpotLight->SetRelativeLocation(LightRightSide);
	}
	else if (FloatValue < 0) {
		FlipbookComp->SetRelativeRotation(FRotator(0, -90, 0));
		FVector LightLeftSide = FVector(2, -1, 6);
		SpotLight->SetRelativeLocation(LightLeftSide);
	}
}

void ADiggerCharacter::Attack(const FInputActionInstance& Instance) {
	if (State.Equals(ATTACK_STATE) || State.Equals(JUMP_STATE) || State.Equals(DIG_STATE)) return;

		TArray<AActor*> AttackArray;
		UGameplayStatics::GetAllActorsWithTag(this, TEXT("Attack"), AttackArray);
		if (AttackArray.Num() > 0) return;
		//UE_LOG(LogTemp, Display, TEXT("Num of Attacks: %d"), AttackArray.Num());

		State = ATTACK_STATE;
		FlipbookComp->SetFlipbook(AttackFlipbook);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADiggerCharacter::ResetAttackTimer, AttackFlipbook->GetTotalDuration(), true);
		UE_LOG(LogTemp, Display, TEXT("Sprite Rotation = %f"), FlipbookComp->GetRelativeRotation().Yaw);
		FVector SpawnLocation = GetActorLocation();
		if (FlipbookComp->GetRelativeRotation().Yaw > 0) {
			SpawnLocation.Y += AttackDistOffset;
		}
		else {
			SpawnLocation.Y -= AttackDistOffset;
		}
		auto Projectile = GetWorld()->SpawnActor<AAttack>(AttackBlueprint, SpawnLocation, FlipbookComp->GetRelativeRotation());
}

void ADiggerCharacter::Dig(const FInputActionInstance& Instance) {
	if (State.Equals(ATTACK_STATE) || State.Equals(JUMP_STATE) || State.Equals(DIG_STATE)) return;
	State = DIG_STATE;
	FlipbookComp->SetFlipbook(DigFlipbook);
	GetWorldTimerManager().SetTimer(DigTimerHandle, this, &ADiggerCharacter::ResetDigTimer, DigFlipbook->GetTotalDuration(), true);
}

void ADiggerCharacter::CheckSpriteRotation() {
	if (State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE)) return;
	if (GetVelocity().Length() <= 0) {
		FlipbookComp->SetFlipbook(IdleFlipbook);
		State = IDLE_STATE;
	}
	else {
		FlipbookComp->SetFlipbook(RunningFlipbook);
		State = RUN_STATE;
	}
}

void ADiggerCharacter::CheckSpriteJump() {
	if(State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE)) return;
	bool onGround = GetCharacterMovement()->IsMovingOnGround();

	if (!onGround) {
		State = JUMP_STATE;
		if (GetVelocity().Z < 0) {
			FlipbookComp->SetFlipbook(FallFlipbook);
		}
		else {
			FlipbookComp->SetFlipbook(JumpFlipbook);
		}
	}
}

void ADiggerCharacter::ResetAttackTimer() {
	State = IDLE_STATE;
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	FlipbookComp->SetFlipbook(IdleFlipbook);
}

void ADiggerCharacter::ResetDigTimer() {
	State = IDLE_STATE;
	GetWorldTimerManager().ClearTimer(DigTimerHandle);
	FlipbookComp->SetFlipbook(IdleFlipbook);
}