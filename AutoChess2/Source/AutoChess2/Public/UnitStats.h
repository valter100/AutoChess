// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOCHESS2_API UUnitStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere) TArray<FString> ChangeableStats;
	UPROPERTY(EditAnywhere) int MaxHealth;
	UPROPERTY(EditAnywhere) int MaxHealthVariance;
	UPROPERTY(EditAnywhere) int CurrentHealth;
	UPROPERTY(EditAnywhere) int MaxMana;
	int CurrentMana;
	UPROPERTY(EditAnywhere) int ManaPerHit;
	UPROPERTY(EditAnywhere) int ManaWhenHit;
	UPROPERTY(EditAnywhere) FString Name;
	UPROPERTY(EditAnywhere) float MovementSpeed; 
	UPROPERTY(EditAnywhere) float MovementSpeedVariance; 
	UPROPERTY(EditAnywhere) float Damage;
	UPROPERTY(EditAnywhere) float DamageVariance;
	UPROPERTY(EditAnywhere) float AttackRange;
	UPROPERTY(EditAnywhere) float AttacksPerSecond;
	UPROPERTY(EditAnywhere) float AttacksPerSecondVariance;

	// Sets default values for this component's properties
	UUnitStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FString IncreaseRandomStat();
	FString DecreaseRandomStat();
	int GetMaxHealth();
	int GetCurrentHealth();
	void ChangeCurrentHealth(int ValueChange);
	void SetCurrentHealth(int NewValue);
	int GetMaxMana();
	int GetCurrentMana();
	void ChangeCurrentMana(int ValueChange);
	void SetCurrentMana(int NewValue);
	int GetManaPerHit();
	int GetManaWhenHit();
	FString GetName();
	float GetMovementSpeed();
	float GetDamage();
	float GetAttackRange();
	float GetAttacksPerSecond();
		
};
