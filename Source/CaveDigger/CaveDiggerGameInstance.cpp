// Fill out your copyright notice in the Description page of Project Settings.


#include "CaveDiggerGameInstance.h"

UCaveDiggerGameInstance::UCaveDiggerGameInstance() {

}

int UCaveDiggerGameInstance::GetHealthUpgrades() {
	return HealthUpgrades;
}

int UCaveDiggerGameInstance::GetHelmetUpgrades() {
	return HelmetUpgrades;
}

int UCaveDiggerGameInstance::GetShovelUpgrades() {
	return ShovelUpgrades;
}

int UCaveDiggerGameInstance::GetTimeUpgrades() {
	return TimeUpgrades;
}

int UCaveDiggerGameInstance::GetAttackRangeUpgrades() {
	return AttackRangeUpgrades;
}

void UCaveDiggerGameInstance::IncreaseHealthUpgrade() {
	 HealthUpgrades++;
}

void UCaveDiggerGameInstance::IncreaseHelmetUpgrade() {
	HelmetUpgrades++;
}

void UCaveDiggerGameInstance::IncreaseShovelUpgrade() {
	ShovelUpgrades++;
}

void UCaveDiggerGameInstance::IncreaseTimeUpgrade() {
	TimeUpgrades++;
}

void UCaveDiggerGameInstance::IncreaseAttackRangeUpgrades() {
	AttackRangeUpgrades++;
}

void UCaveDiggerGameInstance::SetTotalPlayerGems(int Gems) {
	TotalPlayerGems = Gems;
}

int UCaveDiggerGameInstance::GetTotalPlayerGems() {
	return TotalPlayerGems;
}