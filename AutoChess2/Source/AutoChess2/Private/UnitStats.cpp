// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStats.h"
#include <Addon.h>

// Sets default values for this component's properties
UUnitStats::UUnitStats()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUnitStats::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UUnitStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FString UUnitStats::IncreaseRandomStat()
{
	if (ChangeableStats.Num() == 0)
		return "";

	int statIndex = FMath::RandRange(0, ChangeableStats.Num() - 1);
	FString ChangedStat = ChangeableStats[statIndex];
	ChangeableStats.RemoveAt(statIndex);

	if (ChangedStat == "Max Health")
	{
		MaxHealth += MaxHealthVariance;
	}
	if (ChangedStat == "Movement Speed")
	{
		MovementSpeed += MovementSpeedVariance;
	}
	if (ChangedStat == "Damage")
	{
		Damage += DamageVariance;
	}
	if (ChangedStat == "Attack Per Second")
	{
		AttacksPerSecond += AttacksPerSecondVariance;
	}

	return ChangedStat;
}

FString UUnitStats::DecreaseRandomStat()
{
	if (ChangeableStats.Num() == 0)
		return "";

	int statIndex = FMath::RandRange(0, ChangeableStats.Num() - 1);
	FString ChangedStat = ChangeableStats[statIndex];
	ChangeableStats.RemoveAt(statIndex);

	if (ChangedStat == "Max Health")
	{
		MaxHealth -= MaxHealthVariance;
	}
	if (ChangedStat == "Movement Speed")
	{
		MovementSpeed -= MovementSpeedVariance;
	}
	if (ChangedStat == "Damage")
	{
		Damage -= DamageVariance;
	}
	if (ChangedStat == "Attack Per Second")
	{
		AttacksPerSecond -= AttacksPerSecondVariance;
	}

	return ChangedStat;
}

int UUnitStats::GetMaxHealth() { return MaxHealth; }

int UUnitStats::GetCurrentHealth() { return CurrentHealth;}

void UUnitStats::ChangeCurrentHealth(int ValueChange)
{
	Addon::Print("HEALTH CHANGED");
	CurrentHealth += ValueChange;
}

void UUnitStats::SetCurrentHealth(int NewValue)
{
	CurrentHealth = NewValue;
}

int UUnitStats::GetMaxMana() { return MaxMana; }

int UUnitStats::GetCurrentMana() { return CurrentMana; }

void UUnitStats::ChangeCurrentMana(int ValueChange)
{
	CurrentMana += ValueChange;
}

void UUnitStats::SetCurrentMana(int NewValue)
{
	CurrentMana = NewValue;
}

int UUnitStats::GetManaPerHit() { return ManaPerHit; }

int UUnitStats::GetManaWhenHit() { return ManaWhenHit; }

FString UUnitStats::GetName() { return Name; }

float UUnitStats::GetMovementSpeed() { return MovementSpeed; }

float UUnitStats::GetDamage() { return Damage; }

float UUnitStats::GetAttackRange() { return AttackRange; }

float UUnitStats::GetAttacksPerSecond() { return AttacksPerSecond; }

