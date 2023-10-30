// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Addon.h"
#include "GameFramework/Actor.h"
#include "UnitShop.generated.h"

UCLASS()
class AUTOCHESS2_API AUnitShop : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	int ShopSize = 6;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> AllUnits;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> AvailableUnits;	
	UPROPERTY(EditAnywhere)
	TArray<AUnit*> SpawnedUnits;

	// Sets default values for this actor's properties
	AUnitShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void AddUnits();
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void RefreshUnits();
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void SpawnUnits();
	UFUNCTION(BlueprintPure, category = "Unit Shop")
	AUnit* GetUnitAtIndex(int UnitIndex);
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void BuyUnit(int UnitIndex);
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void ToggleShop();
};
