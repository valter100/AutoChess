// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementNode.h"
#include "UnitStats.h"
#include "AIBehaviour.h"
#include "Addon.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

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
	AUnit* CurrentTarget;
	bool PickedUp;
	bool IsBought;
	bool OnBoard;
	bool Active;
	bool Dead;
	bool Sell;
	bool IsDead;
	bool IsMoving;
	bool IsAttacking;
	float TimeSinceLastAttack;
	TArray<AUnit*> OpponentUnits;

	FString IncreasedStat;
	FString DecreasedStat;

	virtual void BeginPlay() override;
	virtual void Die();

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
	virtual void Move();
	virtual void Target();
	virtual void Attack();
	virtual void UseAbility();
	virtual void TakeDamage(int DamageTaken);
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDamagedEffect(FVector HitLocation);
	virtual void RemoveCurrentTargetFromList();
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
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void RandomizeStats();
	virtual bool GetDead();
	void SetOpponentUnits(TArray<AUnit*> Units);
	void ResetOnBoard();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetSell();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetIsMoving();	
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetIsMoving(bool NewValue);
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual bool GetIsAttacking();
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetIsAttacking(bool NewValue);
	virtual APlacementNode* GetCurrentNode();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetMovementSpeed();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual float GetAttackSpeed();
};
