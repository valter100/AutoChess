// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitShop.h"
#include "RoundManager.generated.h"


UCLASS()
class AUTOCHESS2_API ARoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AUnitShop* Shop;
		float RoundTimer;
	UPROPERTY(BlueprintReadOnly)
		float TimeBetweenRounds;

	// Sets default values for this actor's properties
	ARoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetShop(AUnitShop* newShop);
	UFUNCTION(BlueprintPure, Category = "Round Manager")
	float GetRoundTimer();
	UFUNCTION(BlueprintPure, Category = "Round Manager")
	float GetTimeLeft();
	UFUNCTION(BlueprintCallable, Category = "Round Manager")
	void SetRoundTimer(float value);
	UFUNCTION(BlueprintPure, Category = "Round Manager")
	float GetTimeBetweenRounds();
	UFUNCTION(BlueprintCallable, Category = "Round Manager")
	void SetTimeBetweenRounds(float NewValue);
};
