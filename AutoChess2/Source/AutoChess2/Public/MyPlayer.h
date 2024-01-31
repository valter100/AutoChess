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
	UPROPERTY(EditAnywhere)
	TArray<AUnit*> OwnedUnits;

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

	UFUNCTION(BlueprintCallable, category = "Player")
	void SetOpponentUnits(TArray<AUnit*> Units);

	UFUNCTION(BlueprintCallable, category = "Player")
	void ResetUnitsOnBoard();

	UFUNCTION(BlueprintPure, category = "Player")
	TArray<AUnit*> GetUnitsOnBoard();	

	UFUNCTION(BlueprintPure, category = "Player")
	bool HasRemainingUnitsOnBoard();

	TArray<AUnit*> GetOwnedUnits();
};
