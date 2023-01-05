// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attack.generated.h"

UCLASS()
class CAVEDIGGER_API AAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleCollider;
	UPROPERTY(EditDefaultsOnly)
	class UPaperFlipbookComponent* FlipbookComp;
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 10;
	UPROPERTY(EditDefaultsOnly)
	float AttackTimer = 2;

	int32 Damage = 1;
	FTimerHandle DestructionTimerHandle;

	void DestroySelf();

};
