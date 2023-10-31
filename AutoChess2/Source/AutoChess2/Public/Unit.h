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

	TSharedPtr<AUnit> Target;
	// Sets default values for this actor's properties
	AUnit();

protected:
	UPROPERTY(EditAnywhere) UTexture2D* ImageTexture;
	UPROPERTY(EditAnywhere) int Health;
	UPROPERTY(EditAnywhere) int Mana;
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
	bool IsDead;
	float TimeSinceLastAttack;
	//UPROPERTY(VisibleAnywhere, Category = "Unit")
	TArray<TSharedPtr<AUnit>> OpponentUnits;
	//UPROPERTY(EditAnywhere, Category = "Unit")
	TSharedPtr<AUnit> CurrentTarget;
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
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual FText statData();
	UFUNCTION(BlueprintPure, category = "Unit")
	virtual UTexture2D* GetImageTex();
	virtual bool GetIsBought();
	virtual void SetIsBought(bool State);
};
