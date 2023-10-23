// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementNode.h"
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
	UPROPERTY(EditAnywhere) int Health;
	UPROPERTY(EditAnywhere) int Mana;
	UPROPERTY(EditAnywhere) FString Name;
	UPROPERTY(EditAnywhere) float MovementSpeed;
	UPROPERTY(EditAnywhere) float Damage;
	UPROPERTY(EditAnywhere) float AttackRange;
	UPROPERTY(EditAnywhere) float AttacksPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit") bool PickedUp;
	TSharedPtr<APlacementNode> CurrentNode;
	TSharedPtr<APlacementNode> LastNode;
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

};
