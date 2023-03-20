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
	int HelmetLightUpgrades = 0;
	int ShovelUpgrades = 0;
	int AttackRangeUpgrades = 0;
	int TimeUpgrades = 0;
	bool HelmetUpgrade = true;
	TMap<UTexture*, int> UpgradeMap;

	//Player Stats
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	int TotalPlayerGems = 2000;
	int MineLevel = 1;
	int TotalPlayerGold = 0;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHealthUpgrades();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHelmetLightUpgrades();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetShovelUpgrades();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTimeUpgrades();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetAttackRangeUpgrades();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetHelmetUpgrade();

	UFUNCTION(BlueprintCallable)
	void IncreaseHealthUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseHelmetLightUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseShovelUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseTimeUpgrade();
	UFUNCTION(BlueprintCallable)
	void IncreaseAttackRangeUpgrades();
	UFUNCTION(BlueprintCallable)
	void SetHelmetUpgrade(bool DoHelmetUpgrade);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalPlayerGems();
	UFUNCTION(BlueprintCallable)
	void SetTotalPlayerGems(int Gems);
	UFUNCTION(BlueprintCallable)
	void AddGems(int Gems);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMineLevel();
	UFUNCTION(BlueprintCallable)
	void IncreaseMineLevel();
	UFUNCTION(BlueprintCallable)
	void SetMineLevel(int NewMineLevel);

	UFUNCTION(BlueprintCallable)
	void AddPlayerGold(int Gold);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalPlayerGold();

	UFUNCTION(BlueprintCallable)
	void AddToUpgradeMap(UTexture* UpgradeImage);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<UTexture*, int>  GetUpgradeMap();


	UFUNCTION(BlueprintCallable)
	void ResetGameInstance();
};
