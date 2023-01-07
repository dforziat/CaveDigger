// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class CAVEDIGGER_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

private:

	UPROPERTY(EditDefaultsOnly)
	UClass* DirtBlueprint;

	UPROPERTY(EditDefaultsOnly)
	UClass* WallBlueprint;

	UPROPERTY(EditDefaultsOnly)
	UClass* WallCornerBlueprint;

	UPROPERTY(EditDefaultsOnly)
	UClass* ExitBlueprint;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;

	UPROPERTY(EditDefaultsOnly)
	float IncrementDistance = 100;

	UPROPERTY(EditAnywhere)
	int32 MaxRows = 50;

	UPROPERTY(EditAnywhere)
	int32 MaxColumns = 10;

	float MaxGemValue;

	FString LastPlacedObject = "Dirt";


	void GenerateLevel();
	void SpawnWalls();
	void ChooseRandomObject();
};
