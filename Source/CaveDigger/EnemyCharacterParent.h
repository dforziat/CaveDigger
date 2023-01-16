// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyCharacterParent.generated.h"

UCLASS()
class CAVEDIGGER_API AEnemyCharacterParent : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RecieveDamage(int32 Damage);

private:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere)
	class UPointLightComponent* PointLight;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* DamageSound;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* BloodSystem;

	int32 Health = 1;



};
