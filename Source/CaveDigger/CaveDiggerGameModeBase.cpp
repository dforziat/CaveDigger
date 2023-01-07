// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"

void ACaveDiggerGameModeBase::BeginPlay() {
	Super::BeginPlay();

	//Start Timer
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ACaveDiggerGameModeBase::GameOver, GameTime, true);
}

void ACaveDiggerGameModeBase::AddScore(float Value) {
	Score += Value;
}

float ACaveDiggerGameModeBase::GetScore() {
	return Score;
}

float ACaveDiggerGameModeBase::GetRequiredScore() {
	return RequiredScore;
}

int ACaveDiggerGameModeBase::GetGameTimeRemaing() {
	return (int)GetWorldTimerManager().GetTimerRemaining(GameTimerHandle);
}

void ACaveDiggerGameModeBase::GameOver() {

	GetWorldTimerManager().ClearTimer(GameTimerHandle);

}

