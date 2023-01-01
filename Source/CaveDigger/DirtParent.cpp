// Fill out your copyright notice in the Description page of Project Settings.

#include "DirtParent.h"
#include "GemParent.h"


// Sets default values
ADirtParent::ADirtParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADirtParent::BeginPlay()
{
	Super::BeginPlay();
}


void ADirtParent::TakeDigDamage() {
	DamageStage += 1;
	if(Health <= DamageStage) {
		if (GemBluePrint != nullptr) {
			GetWorld()->SpawnActor<AGemParent>(GemBluePrint, GetActorLocation(), GetActorRotation());
		}
		Destroy();
		return;
	}
	StaticMeshComp->SetMaterial(0, MaterialList[DamageStage - 1]);
}

void ADirtParent::DropGem() {

}

