// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DirtParent.h"
#include "EnemyCharacterParent.h"
#include "CaveDiggerGameInstance.h"




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

	auto GameInstance = Cast<UCaveDiggerGameInstance>(GetGameInstance());
	float AttackDuration = FlipbookComp->GetFlipbook()->GetTotalDuration() + (GameInstance->GetAttackRangeUpgrades() * .1);
	GetWorldTimerManager().SetTimer(DestructionTimerHandle, this, &AAttack::DestroySelf, AttackDuration, true);
	OnActorBeginOverlap.AddDynamic(this, &AAttack::OnActorOverlap);

}

// Called every frame
void AAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttack::DestroySelf() {
	Destroy();
}

void AAttack::OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	UE_LOG(LogTemp, Warning, TEXT("Attack Overlap Actor with %s"), *OtherActor->GetActorNameOrLabel());
	if (OtherActor->ActorHasTag("Dirt")) {
		auto Dirt = Cast<ADirtParent>(OtherActor);
		Dirt->TakeDigDamage();
	}
	else if (OtherActor->ActorHasTag("Enemy")) {
		auto Enemy = Cast<AEnemyCharacterParent>(OtherActor);
		Enemy->RecieveDamage(Damage);
	}
	Destroy();
}