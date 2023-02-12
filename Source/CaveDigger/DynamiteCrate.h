// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamiteCrate.generated.h"

UCLASS()
class CAVEDIGGER_API ADynamiteCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamiteCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UPointLightComponent* PointLight;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeepSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ExplosionSound;

	float DetonationTime = 3;
	bool HasBeenTouched = false;

};
