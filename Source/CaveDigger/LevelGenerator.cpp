// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
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
	SpawnWalls();
	GenerateLevel();
}


void ALevelGenerator::GenerateLevel() {
	int32 RowIncrementer = 0;
	int32 ColumnIncrementer = 0;
	FVector SpawnLocation = StartLocation;


	while (RowIncrementer < MaxRows) {
		while (ColumnIncrementer < MaxColumns) {
			ChooseRandomObject(SpawnLocation);
			SpawnLocation += FVector(0, IncrementDistance, 0);
			ColumnIncrementer++;
		}
		RowIncrementer++;
		SpawnLocation = FVector(StartLocation.X, StartLocation.Y,(-RowIncrementer * IncrementDistance) + StartLocation.Z);
		ColumnIncrementer = 0;
	}
		//SpawnExit
		GetWorld()->SpawnActor<AActor>(ExitBlueprint, FVector(StartLocation.X, StartLocation.Y + ((MaxColumns - 1) * IncrementDistance), StartLocation.Z + (-MaxRows * IncrementDistance)), FRotator::ZeroRotator);
}

void ALevelGenerator::ChooseRandomObject(FVector SpawnLocation) {

	//force spawn of hole after enemy to provide movement room
	if (LastPlacedObject.Equals(TEXT("Enemy"))) {
		LastPlacedObject = TEXT("Hole");
		return;
	}


	int RandomNum = FMath::RandRange(1, 30);
	switch (RandomNum) {
	//spawn enemies
		case 1:
			GetWorld()->SpawnActor<AActor>(GrubBlueprint, SpawnLocation, FRotator::ZeroRotator);
			LastPlacedObject = TEXT("Enemy");
			break;
	//spawn hazards
		case 2:
			GetWorld()->SpawnActor<AActor>(SpikeBlueprint, SpawnLocation, FRotator::ZeroRotator);
			LastPlacedObject = TEXT("Hazard");
			break;
	//spawn Gems
		case 3:
			GetWorld()->SpawnActor<AActor>(ChooseGem(), SpawnLocation, FRotator::ZeroRotator);
			LastPlacedObject = TEXT("Gem");
			break;
	//spawn hole
		case 4:
			LastPlacedObject = TEXT("Hole");
			break;
	//spawn dirt as default
		default:
			GetWorld()->SpawnActor<AActor>(DirtBlueprint, SpawnLocation, FRotator::ZeroRotator);
			LastPlacedObject = TEXT("Dirt");
			break;
	}
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

UClass* ALevelGenerator::ChooseGem() {
	int RandomNum = FMath::RandRange(1, 3);
	switch (RandomNum) {
		case 1:
			return EmeraldDirtBlueprint;
			break;
		case 2:
			return RubyDirtBlueprint;
			break;
		case 3:
			return SapphireDirtBlueprint;
			break;
		default:
			return EmeraldDirtBlueprint;
			break;
	}
}

