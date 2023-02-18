// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamiteCrate.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"



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

	FHitResult HitResult;
	//bool hit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), );
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0,0,100), FColor::Red, false, 5);

	Destroy();
	//Do 4 traces (sphere?) up/down/left/right and deal damage to anything in contact. 

}

