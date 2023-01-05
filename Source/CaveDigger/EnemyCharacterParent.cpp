// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterParent.h"
#include "PaperFlipbookComponent.h"
#include "Components/PointLightComponent.h"


// Sets default values
AEnemyCharacterParent::AEnemyCharacterParent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyCharacterParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacterParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacterParent::RecieveDamage(int32 Damage) {
	Health -= Damage;
	if (Health <= 0) {
		Destroy();
	}
}

