// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirtParent.generated.h"

UCLASS()
class CAVEDIGGER_API ADirtParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirtParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void TakeDigDamage(FVector DamageLocation = FVector::ZeroVector);

private:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterial*> MaterialList;

	UPROPERTY(EditDefaultsOnly)
	UClass* GemBluePrint;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* DigSound;


	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* DirtParticleSystem;


	int32 DamageStage = 0;
	int32 Health = 3;

	
	void DropGem();
};
