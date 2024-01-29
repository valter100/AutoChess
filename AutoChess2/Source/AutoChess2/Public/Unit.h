// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementNode.h"
#include "UnitStats.h"
#include "Addon.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

class UAIBehaviour;

UCLASS(Abstract)
class AUTOCHESS2_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AUnit();

protected:
	UPROPERTY(EditAnywhere) UTexture2D* ImageTexture;
	UPROPERTY(EditAnywhere) int Cost;
	UPROPERTY(EditAnywhere) UUnitStats* stats;
	UPROPERTY(EditAnywhere) UAIBehaviour* AIBehaviour;

	APlacementNode* HoveredNode;
	APlacementNode* CurrentNode;
	APlacementNode* LastNode;
	bool PickedUp;
	bool IsBought;
	bool OnBoard;
	bool Active;
	bool Sell;
	bool IsDead;

	FString IncreasedStat;
	FString DecreasedStat;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetPickedUp(bool state);
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetPickedUp();
	virtual void MoveToMouse();
	virtual void Place();
	virtual void Lift();
	virtual void ReceiveDamage(int DamageTaken);
	virtual int GetHealth();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetHealthPercentage();	
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetManaPercentage();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual FText GetNameOfUnit();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual FText statData();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual FText AdvancedStatData();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual UTexture2D* GetImageTex();
	virtual bool GetIsBought();
	virtual void SetIsBought(bool State);
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetCurrentNode(APlacementNode* NewNode);
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetOnBoard(bool state);	
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetOnBoard();
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetActive(bool state);
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetActive();
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetCost(int NewCost);
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual int GetCost();
	virtual bool GetDead();
	void SetOpponentUnits(TArray<AUnit*> Units);
	void ResetOnBoard();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetSell();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetIsMoving();	
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetIsAttacking();
	virtual APlacementNode* GetCurrentNode();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetMovementSpeed();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetAttackSpeed();
	virtual UAIBehaviour* GetBehaviour();
};
