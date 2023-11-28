// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitStats.h"

// Sets default values for this component's properties
UUnitStats::UUnitStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUnitStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UUnitStats::IncreaseRandomStat()
{
	int statIndex = FMath::RandRange(0, ChangeableStats.Num());
	//ChangeableStats.RemoveAt(statIndex);

	if (statIndex == 0)
	{
		MaxHealth += MaxHealthVariance;
		return "Max Health";
	}
	if (statIndex == 1)
	{
		MovementSpeed += MovementSpeedVariance;
		return "Movement Speed";
	}
	if (statIndex == 2)
	{
		Damage += DamageVariance;
		return "Damage";
	}
	if (statIndex == 3)
	{
		AttacksPerSecond += AttacksPerSecondVariance;
		return "Attack Per Second";
	}

	return "";
}

FString UUnitStats::DecreaseRandomStat()
{
	int statIndex = FMath::RandRange(0, ChangeableStats.Num());

	//ChangeableStats.RemoveAt(statIndex);

	if (statIndex == 0)
	{
		MaxHealth -= MaxHealthVariance;
		return "Max Health";
	}
	if (statIndex == 1)
	{
		MovementSpeed -= MovementSpeedVariance;
		return "Movement Speed";
	}
	if (statIndex == 2)
	{
		Damage -= DamageVariance;
		return "Damage";
	}
	if (statIndex == 3)
	{
		AttacksPerSecond -= AttacksPerSecondVariance;
		return "Attack Per Second";
	}

	return "";
}

int UUnitStats::GetMaxHealth() { return MaxHealth; }

int UUnitStats::GetCurrentHealth() { return CurrentHealth;}

void UUnitStats::ChangeCurrentHealth(int ValueChange)
{
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

//UUnitStats::Stat UUnitStats::GetRandomStat()
//{
//	int randomStatIndex = FMath::RandRange(0, (int)Stat::LastElement) - 1;
//	Stat randomStat = Stat(randomStatIndex);
//	return randomStat;
//}

