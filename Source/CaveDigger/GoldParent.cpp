// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldParent.h"
//#include "Components/BoxComponent.h"
//#include "PaperFlipbookComponent.h"
//#include "Components/PointLightComponent.h"
//#include "Components/WidgetComponent.h"

// Sets default values
AGoldParent::AGoldParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	//SetRootComponent(BoxComp);
	//FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook Comp"));
	//FlipbookComp->SetupAttachment(RootComponent);
	//PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	//PointLight->SetupAttachment(RootComponent);
	//WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	//WidgetComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGoldParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AGemParent::GetValue() {
	return Value;
}
