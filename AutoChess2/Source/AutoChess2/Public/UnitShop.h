// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "NodeManager.h"
#include <MyPlayer.h>
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
	int StartCurrency;
	int Currency = 0;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> AllUnits;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> AvailableUnits;	
	UPROPERTY(EditAnywhere)
	TArray<AUnit*> SpawnedUnits;
	UPROPERTY(EditAnywhere)
	ANodeManager* NodeManager;
	UPROPERTY(EditAnywhere)
	AMyPlayer* Player;

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
	void AddSpawnUnits();	
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void RefreshSpawnUnits();
	UFUNCTION(BlueprintPure, category = "Unit Shop")
	AUnit* GetUnitAtIndex(int UnitIndex);
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	bool BuyUnit(int UnitIndex);
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void SetCurrency(int newAmount);	
	UFUNCTION(BlueprintPure, category = "Unit Shop")
	int GetCurrency();
	UFUNCTION(BlueprintPure, category = "Unit Shop")
	int GetStartCurrency();
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void AddCurrency(int currencyAdded);
	UFUNCTION(BlueprintCallable, category = "Unit Shop")
	void SellUnit(AUnit* SellUnit);
};
