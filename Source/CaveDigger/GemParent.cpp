// Fill out your copyright notice in the Description page of Project Settings.


#include "GemParent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"



// Sets default values
AGemParent::AGemParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(BoxComp);

	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Comp"));
	FlipbookComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGemParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGemParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


