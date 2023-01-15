// Fill out your copyright notice in the Description page of Project Settings.


#include "Boulder.h"

// Sets default values
ABoulder::ABoulder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABoulder::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ABoulder::OnHit);
	OnActorHit.AddDynamic(this, &ABoulder::OnActHit);
}

// Called every frame
void ABoulder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoulder::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Boulder hit: %s") , *OtherActor->GetActorNameOrLabel());
	UE_LOG(LogTemp, Warning, TEXT("Boulder Comp Hit!"));
}

void ABoulder::OnActHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("Boulder Actor Hit!"));
}

