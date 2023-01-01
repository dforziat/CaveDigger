// Copyright Epic Games, Inc. All Rights Reserved.


#include "CaveDiggerGameModeBase.h"



void ACaveDiggerGameModeBase::AddScore(float Value) {
	Score += Value;
}

float ACaveDiggerGameModeBase::GetScore() {
	return Score;
}

