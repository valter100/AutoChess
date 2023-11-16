// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Unit.h>
#include "GameFramework/Actor.h"
#include "MyPlayer.generated.h"

UCLASS()
class AUTOCHESS2_API AMyPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	//UPROPERTY(EditAnywhere)
	//TArray<AUnit*> ActiveUnits;	
	UPROPERTY(EditAnywhere)
	TArray<AUnit*> OwnedUnits;
	//TArray<AUnit*> OpponentUnits;
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, category = "Player")
		void AddUnitToOwnedUnits(AUnit* NewUnit);	
	UFUNCTION(BlueprintCallable, category = "Player")
		void RemoveUnitFromOwnedUnits(AUnit* RemovedUnit);
	UFUNCTION(BlueprintCallable, category = "Player")
	void ActivateUnits();
	TArray<AUnit*> GetOwnedUnits();
	UFUNCTION(BlueprintCallable, category = "Player")
	void SetOpponentUnits(TArray<AUnit*> Units);
	UFUNCTION(BlueprintPure, category = "Player")
	TArray<AUnit*> GetUnitsOnBoard();	
	UFUNCTION(BlueprintPure, category = "Player")
	bool HasRemainingUnitsOnBoard();
	UFUNCTION(BlueprintCallable, category = "Player")
	void ResetUnitsOnBoard();
};
