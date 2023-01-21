// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CaveDiggerGameInstance.h"
#include "DiggerCharacter.h"




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
		RemovePauseScreen();
	}
	else {
		GameIsPaused = true;
		GetWorldTimerManager().PauseTimer(GameTimerHandle);
		DisplayPauseScreen();
	}
	UGameplayStatics::PlaySound2D(this, PauseSound);
	UGameplayStatics::SetGamePaused(this, GameIsPaused);
}

void ACaveDiggerGameModeBase::TimeOver() {
	IsTimeOver = true;
	if (auto DiggerCharacter = Cast<ADiggerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))) {
		DiggerCharacter->Die();
	}
}

