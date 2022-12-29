// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAttack::AAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capusle Collider"));
	SetRootComponent(CapsuleCollider);
	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Comp"));
	FlipbookComp->SetupAttachment(CapsuleCollider);
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

// Called when the game starts or when spawned
void AAttack::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestructionTimerHandle, this, &AAttack::DestroySelf, FlipbookComp->GetFlipbook()->GetTotalDuration(), true);
}

// Called every frame
void AAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttack::DestroySelf() {
	Destroy();
}

