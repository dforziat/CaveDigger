// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacterParent.h"
#include "GrubEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CAVEDIGGER_API AGrubEnemy : public AEnemyCharacterParent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGrubEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	float MoveSpeed = .2;
	
	void Move();
};
