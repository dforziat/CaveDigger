// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "DirtParent.h"
#include "Kismet/GameplayStatics.h"
#include "CaveDiggerGameModeBase.h"



// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (auto GameMode = Cast<ACaveDiggerGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		MaxGemValue = GameMode->GetRequiredScore() * 1.5;
	}

	SpawnWalls();
	GenerateLevel();
}


void ALevelGenerator::GenerateLevel() {
	int32 RowIncrementer = 0;
	int32 ColumnIncrementer = 0;
	FVector SpawnLocation = StartLocation;


	while (RowIncrementer < MaxRows) {
		while (ColumnIncrementer < MaxColumns) {
			//Spawn Dirt
			ChooseRandomObject();
			auto Dirt = GetWorld()->SpawnActor<ADirtParent>(DirtBlueprint, SpawnLocation, FRotator::ZeroRotator);
			LastPlacedObject = TEXT("Dirt");
			SpawnLocation += FVector(0, IncrementDistance, 0);
			ColumnIncrementer++;
		}
		RowIncrementer++;
		SpawnLocation = FVector(StartLocation.X, StartLocation.Y,(-RowIncrementer * IncrementDistance) + StartLocation.Z);
		ColumnIncrementer = 0;
	}
}

void ALevelGenerator::ChooseRandomObject() {
	//Decide which item/object/enemy to place into the level. 
}

void ALevelGenerator::SpawnWalls() {
	//Spawn Corners first
	FVector LeftCorner = FVector(StartLocation.X, StartLocation.Y - IncrementDistance, StartLocation.Z + (IncrementDistance * 2));
	GetWorld()->SpawnActor<AActor>(WallCornerBlueprint, LeftCorner, FRotator::ZeroRotator);
	FVector RightCorner = FVector(StartLocation.X, StartLocation.Y + (IncrementDistance * MaxColumns), StartLocation.Z + (IncrementDistance * 2));
	GetWorld()->SpawnActor<AActor>(WallCornerBlueprint, RightCorner, FRotator(-90,0,0));

	//Spawn Walls
	int32 RowIncrementer = -1;
	while (RowIncrementer < MaxRows + 1) {
		//Left Wall
		GetWorld()->SpawnActor<AActor>(WallBlueprint, FVector(StartLocation.X, StartLocation.Y - IncrementDistance, StartLocation.Z + (IncrementDistance * -RowIncrementer)), FRotator::ZeroRotator);

		//Right Wall
		GetWorld()->SpawnActor<AActor>(WallBlueprint, FVector(StartLocation.X, StartLocation.Y + (IncrementDistance * MaxColumns), StartLocation.Z + (IncrementDistance * -RowIncrementer)), FRotator(180, 0, 0));
		RowIncrementer++;
	}

	//Spawn Floor
	int32 FloorIncrementer = 0;
	while (FloorIncrementer < MaxColumns) {

		//Floor
		GetWorld()->SpawnActor<AActor>(WallBlueprint, FVector(StartLocation.X, StartLocation.Y + (IncrementDistance * FloorIncrementer), StartLocation.Z + (IncrementDistance * -MaxRows)), FRotator(0, 0, -90));
		FloorIncrementer++;
	}
}

