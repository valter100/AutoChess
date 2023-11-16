// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementNode.h"
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
	UPROPERTY(EditAnywhere) int MaxHealth;
	UPROPERTY(EditAnywhere) int CurrentHealth;
	UPROPERTY(EditAnywhere) int MaxMana;
	UPROPERTY(EditAnywhere) int CurrentMana;
	UPROPERTY(EditAnywhere) int ManaPerHit;
	UPROPERTY(EditAnywhere) FString Name;
	UPROPERTY(EditAnywhere) float MovementSpeed;
	UPROPERTY(EditAnywhere) float Damage;
	UPROPERTY(EditAnywhere) float AttackRange;
	UPROPERTY(EditAnywhere) float AttacksPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit") bool PickedUp;
	UPROPERTY(EditAnywhere) APlacementNode* HoveredNode;
	UPROPERTY(EditAnywhere) APlacementNode* CurrentNode;
	UPROPERTY(EditAnywhere) APlacementNode* LastNode;
	UPROPERTY(EditAnywhere) bool IsBought;
	UPROPERTY(EditAnywhere) bool OnBoard;
	UPROPERTY(EditAnywhere) bool Active;
	UPROPERTY(EditAnywhere) bool Dead;
	UPROPERTY(EditAnywhere) int Cost;
	UPROPERTY(EditAnywhere) TArray<AUnit*> OpponentUnits;

	bool IsDead;
	float TimeSinceLastAttack;
	UPROPERTY(EditAnywhere) AUnit* CurrentTarget;
	//Ability ability;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void SetPickedUp(bool state);
	UFUNCTION(BlueprintCallable, category = "Unit")
	virtual void TogglePickedUp();
	virtual void MoveToMouse();
	virtual void Place();
	virtual void Lift();
	virtual void Move();
	virtual void Target();
	virtual void Attack();
	virtual void UseAbility();
	virtual void TakeDamage(int DamageTaken);
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
};
