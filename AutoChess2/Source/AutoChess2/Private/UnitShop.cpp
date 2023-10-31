// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitShop.h"

// Sets default values
AUnitShop::AUnitShop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUnitShop::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitShop::AddUnits()
{
	for (int i = 0; i < ShopSize; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, AllUnits.Num() - 1);
		AvailableUnits.Add(AllUnits[RandomIndex]);
	}

	AddSpawnUnits();
}

void AUnitShop::RefreshUnits()
{

	for (int i = 0; i < ShopSize; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, AllUnits.Num() - 1);

		AvailableUnits[i] = AllUnits[RandomIndex];

	}

	for (AUnit* unit : SpawnedUnits)
	{
		if (!unit->GetIsBought())
		{
			unit->Destroy();
		}
		
		SpawnedUnits.Remove(unit);
	}

	RefreshSpawnUnits();
}

void AUnitShop::AddSpawnUnits()
{
	for (UClass* i : AvailableUnits)
	{
		SpawnedUnits.Add(GetWorld()->SpawnActor<AUnit>(i));
	}

	FVector spawnPosition(-10000, 0, 0);

	for (AUnit* i : SpawnedUnits)
	{
		i->SetActorLocation(spawnPosition);
	}
}

void AUnitShop::RefreshSpawnUnits()
{
	for (int i = 0; i < SpawnedUnits.Num(); i++)
	{
		SpawnedUnits.RemoveAt(i);
		i--;
	}

	for (UClass* i : AvailableUnits)
	{
		SpawnedUnits.Add(GetWorld()->SpawnActor<AUnit>(i));
	}

	FVector spawnPosition(-10000, 0, 0);

	for (AUnit* i : SpawnedUnits)
	{
		i->SetActorLocation(spawnPosition);
	}
}

void AUnitShop::BuyUnit(int UnitIndex)
{
	AvailableUnits[UnitIndex] = nullptr;

	AUnit* SpawnedUnit = SpawnedUnits[UnitIndex];
	SpawnedUnit->TogglePickedUp();
	SpawnedUnit->SetIsBought(true);
}

void AUnitShop::ToggleShop()
{
	Addon::Print("Shop Toggled!");
}

AUnit* AUnitShop::GetUnitAtIndex(int UnitIndex)
{
	return SpawnedUnits[UnitIndex];
}

