// Fill out your copyright notice in the Description page of Project Settings.


#include "GrubEnemy.h"
#include "PaperFlipbookComponent.h"


AGrubEnemy::AGrubEnemy() {

}

// Called when the game starts or when spawned
void AGrubEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrubEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AGrubEnemy::Move() {
	if (GetVelocity().Length() == 0) {
		MoveSpeed = MoveSpeed * -1;
	}
	AddMovementInput(GetActorRightVector() * MoveSpeed);

	if (MoveSpeed < 0) {
		GetSprite()->SetRelativeRotation(FRotator(0, 90, 0));
	}
	else {
		GetSprite()->SetRelativeRotation(FRotator(0, -90, 0));
	}
	

}