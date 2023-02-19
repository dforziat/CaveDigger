// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamiteCrate.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DiggerCharacter.h"
#include "DirtParent.h"
#include "EnemyCharacterParent.h"




// Sets default values
ADynamiteCrate::ADynamiteCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADynamiteCrate::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ADynamiteCrate::OnMeshHit);

	
}

// Called every frame
void ADynamiteCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamiteCrate::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("Dynamite ON HIT works!!!"));
	if (!HasBeenTouched &&(OtherActor->ActorHasTag(TEXT("Player")) || OtherActor->ActorHasTag(TEXT("Enemy")))) {
		StartCountdown();
		HasBeenTouched = true;
	}
}

void ADynamiteCrate::Explode() {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, GetActorLocation());
	FCollisionShape SweepShape = FCollisionShape::MakeSphere(ExplosionRadius);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult HitResult;
	bool UpHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector(0, 0, ExplosionDistance), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, SweepShape, QueryParams);
	if (UpHit) {
		CheckExplosionTargets(HitResult);
	}
	bool DownHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector(0, 0, -ExplosionDistance), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, SweepShape, QueryParams);
	if (DownHit) {
		CheckExplosionTargets(HitResult);
	}
	bool LeftHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector(0, -ExplosionDistance, 0), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, SweepShape, QueryParams);
	if (LeftHit) {
		CheckExplosionTargets(HitResult);
	}
	bool RightHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + FVector(0, ExplosionDistance, 0), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, SweepShape, QueryParams);
	if (RightHit) {
		CheckExplosionTargets(HitResult);
	}

	Destroy();

}

void ADynamiteCrate::CheckExplosionTargets(FHitResult HitResult) {
	if (auto DiggerCharacter = Cast<ADiggerCharacter>(HitResult.GetActor())) {
		DiggerCharacter->RecieveDamage(Damage, GetActorLocation());
	}
	else if (auto Dirt = Cast<ADirtParent>(HitResult.GetActor())) {
		Dirt->TakeDigDamage(HitResult.ImpactPoint, Damage);
	}
	else if (auto Enemy = Cast<AEnemyCharacterParent>(HitResult.GetActor())) {
		Enemy->RecieveDamage(Damage);
	}
}

