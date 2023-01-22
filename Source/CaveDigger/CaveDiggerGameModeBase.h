// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CaveDiggerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAVEDIGGER_API ACaveDiggerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int GetGameTimeRemaing();

	UFUNCTION(BlueprintCallable)
    void StartGameTimer();


	UFUNCTION(BlueprintCallable)
	void GameOver();


	UFUNCTION(BlueprintCallable)
	void TimeOver();

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayGameOverScreen();

	UFUNCTION(BlueprintCallable)
	void GameWin();

	UFUNCTION(BlueprintCallable)
	void TogglePause();

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayPauseScreen();

	UFUNCTION(BlueprintImplementableEvent)
	void RemovePauseScreen();

	UPROPERTY(BluePrintReadOnly)
	bool GameIsPaused = false;

	UPROPERTY(BluePrintReadOnly)
	bool IsTimeOver = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int GameTime = 30;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* PauseSound;

	FTimerHandle GameTimerHandle;

	class UCaveDiggerGameInstance* GameInstance;



	
};
