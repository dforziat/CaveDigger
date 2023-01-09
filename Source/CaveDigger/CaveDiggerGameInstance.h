// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CaveDiggerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAVEDIGGER_API UCaveDiggerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCaveDiggerGameInstance();

private:

	//Upgrades
	int HealthUpgrades = 0;
	int HelmetUpgrades = 0;
	int ShovelUpgrades = 0;
	int AttackRangeUpgrades = 0;
	int TimeUpgrades = 0;

	//Player Stats
	int TotalPlayerGems = 22;

public:

	UFUNCTION(BlueprintCallable)
	int GetHealthUpgrades();
	UFUNCTION(BlueprintCallable)
	int GetHelmetUpgrades();
	UFUNCTION(BlueprintCallable)
	int GetShovelUpgrades();
	UFUNCTION(BlueprintCallable)
	int GetTimeUpgrades();
	UFUNCTION(BlueprintCallable)
	int GetAttackRangeUpgrades();

	UFUNCTION(BlueprintCallable)
	void IncreaseHealthUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseHelmetUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseShovelUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseTimeUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseAttackRangeUpgrades();

	UFUNCTION(BlueprintCallable)
	int GetTotalPlayerGems();
	UFUNCTION(BlueprintCallable)
	void SetTotalPlayerGems(int Gems);
	
};
