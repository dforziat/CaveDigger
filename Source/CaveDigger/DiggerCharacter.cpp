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
#include "Components/PointLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "DirtParent.h"
#include "GemParent.h"
#include "CaveDiggerGameModeBase.h"
#include "CaveDiggerGameInstance.h"



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
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ADiggerCharacter::BeginPlay()
{
	Super::BeginPlay();	
	OnActorBeginOverlap.AddDynamic(this, &ADiggerCharacter::OnActorOverlap);

	InitUpgrades();
	
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
	Input->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ADiggerCharacter::PauseGame);

}


void ADiggerCharacter::MoveRight(const FInputActionInstance& Instance) {
	if (State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE) || State.Equals(DEATH_STATE)) return;
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
	if (State.Equals(ATTACK_STATE) || State.Equals(JUMP_STATE) || State.Equals(DIG_STATE) || State.Equals(DEATH_STATE)) return;

		TArray<AActor*> AttackArray;
		UGameplayStatics::GetAllActorsWithTag(this, TEXT("Attack"), AttackArray);
		if (AttackArray.Num() > 0) return;

		State = ATTACK_STATE;
		FlipbookComp->SetFlipbook(AttackFlipbook);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADiggerCharacter::ResetAttackTimer, AttackFlipbook->GetTotalDuration(), true);
		UE_LOG(LogTemp, Display, TEXT("Sprite Rotation = %f"), FlipbookComp->GetRelativeRotation().Yaw);
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 10;
		if (FlipbookComp->GetRelativeRotation().Yaw > 0) {
			SpawnLocation.Y += AttackDistOffset;
		}
		else {
			SpawnLocation.Y -= AttackDistOffset;
		}
		auto Projectile = GetWorld()->SpawnActor<AAttack>(AttackBlueprint, SpawnLocation, FlipbookComp->GetRelativeRotation());
}

void ADiggerCharacter::Dig(const FInputActionInstance& Instance) {
	if (State.Equals(ATTACK_STATE) || State.Equals(JUMP_STATE) || State.Equals(DIG_STATE) || State.Equals(DEATH_STATE)) return;
	State = DIG_STATE;
	FlipbookComp->SetFlipbook(DigFlipbook);
	GetWorldTimerManager().SetTimer(DigTimerHandle, this, &ADiggerCharacter::ResetDigTimer, DigFlipbook->GetTotalDuration(), true);

	//Create LineCast
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult HitResult;
	bool hit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector(0,0,-100), ECollisionChannel::ECC_Pawn, QueryParams);
	if (hit) {
		if (HitResult.GetActor()->ActorHasTag(TEXT("Dirt"))) {
			Cast<ADirtParent>(HitResult.GetActor())->TakeDigDamage();
		}
	}
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0, 0, -100), FColor::Red, true, 5);

}

void ADiggerCharacter::CheckSpriteRotation() {
	if (State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE) || State.Equals(DEATH_STATE)) return;
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
	if(State.Equals(ATTACK_STATE) || State.Equals(DIG_STATE) || State.Equals(DEATH_STATE)) return;
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

void ADiggerCharacter::OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Player On overlap with %s"), *OtherActor->GetActorNameOrLabel());
	if (OtherActor->ActorHasTag("Gem")) {
		UE_LOG(LogTemp, Warning, TEXT("Player On overlap with Gem"));
		auto Gem = Cast<AGemParent>(OtherActor);
		//Get GameMode and Add Gem Value to it. 
		if (GameInstance != nullptr) {
			GameInstance->AddGems(Gem->Value);
		}
		UGameplayStatics::PlaySoundAtLocation(this, GemPickupSound, GetActorLocation());
		Gem->Destroy();
	}
	else if (OtherActor->ActorHasTag("Enemy") || OtherActor->ActorHasTag("Hazard")) {
		//DrawDebugPoint(GetWorld(), LaunchForce, 100, FColor::Red, true);
		RecieveDamage(1, OtherActor->GetActorLocation());
	}
}



void ADiggerCharacter::RecieveDamage(int32 Damage, FVector DamageLocation) {
	if (IsInvincible || State.Equals(DEATH_STATE)) return;
	UE_LOG(LogTemp, Warning, TEXT("Took Damage from Enemy!"));

	UGameplayStatics::PlaySoundAtLocation(this, HurtSound, GetActorLocation());
	//Manage Invincible stuff
	IsInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibleTimerHandle, this, &ADiggerCharacter::ResetInvincibleTimer, InvincibleTime, true);

	//Knockback
	FVector LaunchVector = DamageLocation + GetActorLocation();
	FVector LaunchForce = LaunchVector.GetSafeNormal() * 300;
	LaunchCharacter(LaunchForce, true, true);

	FlickerSprite();


	Health -= Damage;
	if (Health <= 0) {
		Die();
	}
		
}

void ADiggerCharacter::ResetInvincibleTimer() {
	IsInvincible = false;
	GetWorldTimerManager().ClearTimer(InvincibleTimerHandle);
}

int ADiggerCharacter::GetMaxHealth() {
	return MaxHealth;
}

int ADiggerCharacter::GetCurrentHealth() {
	return Health;
}

void ADiggerCharacter::GainHealth() {
	if(Health < MaxHealth) {
		Health++;
	}
}

void ADiggerCharacter::InitUpgrades() {
	GameInstance = Cast<UCaveDiggerGameInstance>(GetGameInstance());
	MaxHealth += GameInstance->GetHealthUpgrades();
	Health = MaxHealth;
	PointLight->AttenuationRadius += (GameInstance->GetHelmetUpgrades() * 50);
}

void ADiggerCharacter::PauseGame(const FInputActionInstance& Instance) {
	if (State.Equals(DEATH_STATE)) return;
	if (auto GameMode = Cast<ACaveDiggerGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		UE_LOG(LogTemp, Warning, TEXT("Pause Pressed"));
		GameMode->TogglePause();
	}
}

void ADiggerCharacter::Die() {
	//End Game
	State = DEATH_STATE;
	FlipbookComp->SetFlipbook(DeadFlipbook);
	DisableInput(UGameplayStatics::GetPlayerController(this, 0));
	if (auto GameMode = Cast<ACaveDiggerGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		GameMode->GameOver();
	}
}