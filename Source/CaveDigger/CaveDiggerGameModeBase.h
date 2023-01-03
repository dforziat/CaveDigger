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

	void AddScore(float Value);
	
	float GetScore();

private:
	UPROPERTY(EditAnywhere)
	float Score = 0;
	
};