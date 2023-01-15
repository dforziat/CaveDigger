// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CaveDiggerGameInstance.h"



void ACaveDiggerGameModeBase::BeginPlay() {
	Super::BeginPlay();
	//Setup Upgrades
	GameInstance = Cast<UCaveDiggerGameInstance>(GetGameInstance());
	GameTime += (GameInstance->GetTimeUpgrades() * 20);
}
	

void ACaveDiggerGameModeBase::StartGameTimer() {
	//Start Timer
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ACaveDiggerGameModeBase::GameOver, GameTime, true);
}

int ACaveDiggerGameModeBase::GetGameTimeRemaing() {
	return (int)GetWorldTimerManager().GetTimerRemaining(GameTimerHandle);
}

void ACaveDiggerGameModeBase::GameOver() {
	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	GameInstance->ResetGameInstance();
	//Display Game Over screen.
	DisplayGameOverScreen();
}

void ACaveDiggerGameModeBase::GameWin() {
	//Show UI for upgrades
	GetWorldTimerManager().PauseTimer(GameTimerHandle);
	GameInstance->IncreaseMineLevel();
	UGameplayStatics::OpenLevel(this, TEXT("UpgradeLevel"));
}

void ACaveDiggerGameModeBase::TogglePause() {
	if (GameIsPaused) {
		GameIsPaused = false;
		GetWorldTimerManager().UnPauseTimer(GameTimerHandle);
	}
	else {
		GameIsPaused = true;
		GetWorldTimerManager().PauseTimer(GameTimerHandle);
	}
	UGameplayStatics::SetGamePaused(this, GameIsPaused);
}

