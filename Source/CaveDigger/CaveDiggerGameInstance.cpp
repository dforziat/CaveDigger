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

void UCaveDiggerGameInstance::AddGems(int Gems) {
	TotalPlayerGems += Gems;
}

int UCaveDiggerGameInstance::GetMineLevel() {
	return MineLevel;
}

void UCaveDiggerGameInstance::IncreaseMineLevel() {
	MineLevel++;
}

void UCaveDiggerGameInstance::SetMineLevel(int NewMineLevel) {
	MineLevel = NewMineLevel;
}

int  UCaveDiggerGameInstance::GetTotalPlayerGold() {
	return TotalPlayerGold;
}
void UCaveDiggerGameInstance::AddPlayerGold(int Gold) {
	TotalPlayerGold = TotalPlayerGold + Gold;
}

void UCaveDiggerGameInstance::AddToUpgradeMap(UTexture* UpgradeImage) {
	if (UpgradeMap.Contains(UpgradeImage)) {
		UpgradeMap.Add(UpgradeImage, UpgradeMap[UpgradeImage] += 1);
	}
	else {
		UpgradeMap.Add(UpgradeImage,1);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Upgrade Map: %s"),);
}

TMap<UTexture*, int> UCaveDiggerGameInstance::GetUpgradeMap() {
	return UpgradeMap;
}

void UCaveDiggerGameInstance::ResetGameInstance() {
	 HealthUpgrades = 0;
	 HelmetUpgrades = 0;
	 ShovelUpgrades = 0;
	 AttackRangeUpgrades = 0;
	 TimeUpgrades = 0;
	 UpgradeMap.Empty();

	//Player Stats
	 TotalPlayerGems = 0;
	 MineLevel = 1;
}