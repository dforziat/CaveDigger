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
	float GetRequiredScore();

	UFUNCTION(BlueprintCallable)
	int GetGameTimeRemaing();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintCallable)
	void GameWin();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int GameTime = 120;

	FTimerHandle GameTimerHandle;

	class UCaveDiggerGameInstance* GameInstance;
	
};
