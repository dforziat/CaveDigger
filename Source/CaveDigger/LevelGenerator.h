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

	UPROPERTY(EditDefaultsOnly, Category = "Dirt Blueprints")
	UClass* DirtBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Dirt Blueprints")
	UClass* WallBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Dirt Blueprints")
	UClass* WallCornerBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Gem Blueprints")
	UClass* EmeraldDirtBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Gem Blueprints")
	UClass* RubyDirtBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Gem Blueprints")
	UClass* SapphireDirtBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = "Enemy Blueprints")
	UClass* GrubBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Hazard Blueprints")
	UClass* SpikeBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Hazard Blueprints")
	UClass* BoulderBlueprint;

	UPROPERTY(EditDefaultsOnly)
	UClass* ExitBlueprint;

	UPROPERTY(EditDefaultsOnly)
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
	void ChooseRandomObject(FVector SpawnLocation);
	UClass* ChooseGem();
	UClass* ChooseHazard();
};
