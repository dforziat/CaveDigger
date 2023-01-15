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

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayGameOverScreen();

	UFUNCTION(BlueprintCallable)
	void GameWin();

	UFUNCTION(BlueprintCallable)
	void TogglePause();

	UPROPERTY()
	bool GameIsPaused = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int GameTime = 120;

	FTimerHandle GameTimerHandle;

	class UCaveDiggerGameInstance* GameInstance;
	
};
