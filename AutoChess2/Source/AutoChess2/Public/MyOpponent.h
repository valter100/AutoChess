// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Unit.h>
#include <Melee.h>
#include <Ranged.h>
#include <PlacementNode.h>
#include <MyPlayer.h>
#include "MyOpponent.generated.h"

UCLASS()
class AUTOCHESS2_API AMyOpponent : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> AllUnits;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AUnit>> RandomizedTeam;

	UPROPERTY(EditAnywhere)
	TArray<AUnit*> SpawnedUnits;

	UPROPERTY(EditAnywhere)
	TArray<APlacementNode*> FrontLine;

	UPROPERTY(EditAnywhere)
	TArray<APlacementNode*> BackLine;

	UPROPERTY(EditAnywhere)
	AMyPlayer* Player;

	// Sets default values for this actor's properties
	AMyOpponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, category = "Opponent")
	void GenerateTeam();

	UFUNCTION(BlueprintCallable, category = "Opponent")
	void SpawnUnits();

	UFUNCTION(BlueprintCallable, category = "Opponent")
	void CleanUpUnits();

	UFUNCTION(BlueprintCallable, category = "Opponent")
	void ActivateUnits();

	UFUNCTION(BlueprintCallable, category = "Opponent")
	void SetOpponentUnits(TArray<AUnit*> Units);

	UFUNCTION(BlueprintPure, category = "Opponent")
	TArray<AUnit*> GetSpawnedUnits();

	UFUNCTION(BlueprintPure, category = "Player")
	bool HasRemainingUnitsOnBoard();

	APlacementNode* GetRandomUnnocupiedNode(TArray<APlacementNode*> NodeArray);
};
