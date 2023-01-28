// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CaveDiggerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAVEDIGGER_API ACaveDiggerGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CameraShake;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int GameTime = 120;

	bool IsCameraShaking = false;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* PauseSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* RumbleSound;

	FTimerHandle GameTimerHandle;

	class UCaveDiggerGameInstance* GameInstance;

	class ADiggerCharacter* DiggerCharacter;

};
