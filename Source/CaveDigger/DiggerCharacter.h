// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputAction.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DiggerCharacter.generated.h"

UCLASS()
class CAVEDIGGER_API ADiggerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiggerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void RecieveDamage(int32 Damage, FVector DamageLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void FlickerSprite();

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	void GainHealth();

	UFUNCTION(BlueprintCallable)
	void Die();

private:
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	class UInputAction* MoveRightAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	UInputAction* AttackAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	UInputAction* DigAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Actions")
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditDefaultsOnly)
	class UPointLightComponent* PointLight;

	UPROPERTY(EditDefaultsOnly)
	UClass* AttackBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UPaperFlipbookComponent* FlipbookComp;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
    class UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* RunningFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* JumpFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* FallFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* AttackFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* DigFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Flipbooks")
	UPaperFlipbook* DeadFlipbook;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HurtSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* GemPickupSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* DigClinkSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AttackSound;


	const FString IDLE_STATE = "Idle";
	const FString RUN_STATE = "Run";
	const FString JUMP_STATE = "Jump";
	const FString ATTACK_STATE = "Attack";
	const FString DIG_STATE = "Dig";
	const FString DEATH_STATE = "Death";


	FString State = IDLE_STATE;
	FTimerHandle AttackTimerHandle;
	FTimerHandle DigTimerHandle;
	FTimerHandle InvincibleTimerHandle;
	class UCaveDiggerGameInstance* GameInstance;
	float AttackDistOffset = 80;
	int Health = 3;
	int MaxHealth = 3;
	bool IsInvincible = false;
	float InvincibleTime = 2;

	void MoveRight(const FInputActionInstance& Instance);
	void Attack(const FInputActionInstance& Instance);
	void Dig(const FInputActionInstance& Instance);
	void PauseGame(const FInputActionInstance& Instance);


	void CheckSpriteRotation();
	void CheckSpriteJump();
	void ResetAttackTimer();
	void ResetDigTimer();
	void ResetInvincibleTimer();

	void InitUpgrades();
};
