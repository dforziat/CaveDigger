// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CaveDiggerGameInstance.h"
#include "DiggerCharacter.h"





void ACaveDiggerGameModeBase::BeginPlay() {
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	DiggerCharacter = Cast<ADiggerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//Setup Upgrades
	GameInstance = Cast<UCaveDiggerGameInstance>(GetGameInstance());
	GameTime += (GameInstance->GetTimeUpgrades() * 20);
}

void ACaveDiggerGameModeBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//Rumble when time runs low
	if (GetWorldTimerManager().GetTimerRemaining(GameTimerHandle) <= 30 && !IsCameraShaking && GetWorldTimerManager().GetTimerRemaining(GameTimerHandle) != -1){
		IsCameraShaking = true;
		UGameplayStatics::PlayWorldCameraShake(this, CameraShake, DiggerCharacter->GetActorLocation(), 1, 10000);
		UGameplayStatics::PlaySound2D(this, RumbleSound);
	}
}
	

void ACaveDiggerGameModeBase::StartGameTimer() {
	//Start Timer
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ACaveDiggerGameModeBase::TimeOver, GameTime, true);
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
	if (DiggerCharacter != nullptr) {
		DiggerCharacter->Die();
	}
}

