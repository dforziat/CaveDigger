// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CaveDiggerGameInstance.h"



void ACaveDiggerGameModeBase::BeginPlay() {
	Super::BeginPlay();
	//Setup Upgrades
	GameInstance = Cast<UCaveDiggerGameInstance>(GetGameInstance());
	GameTime += (GameInstance->GetTimeUpgrades() * 20);
	//Start Timer
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ACaveDiggerGameModeBase::GameOver, GameTime, true);
}



int ACaveDiggerGameModeBase::GetGameTimeRemaing() {
	return (int)GetWorldTimerManager().GetTimerRemaining(GameTimerHandle);
}

void ACaveDiggerGameModeBase::GameOver() {

	GetWorldTimerManager().ClearTimer(GameTimerHandle);

}

void ACaveDiggerGameModeBase::GameWin() {
	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	//Show UI for upgrades
	UGameplayStatics::OpenLevel(this, TEXT("Level"));
}

