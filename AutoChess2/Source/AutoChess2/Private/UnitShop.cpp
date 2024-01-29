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

	RefreshSpawnUnits();
}

void AUnitShop::RefreshSpawnUnits()
{
	for (int i = 0; i < SpawnedUnits.Num(); i++)
	{
		if (SpawnedUnits[i] != nullptr && !SpawnedUnits[i]->GetIsBought())
		{
			SpawnedUnits[i]->Destroy();
		}

		SpawnedUnits.RemoveAt(i);
		i--;
	}

	AddSpawnUnits();
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


bool AUnitShop::BuyUnit(int UnitIndex)
{
	APlacementNode* SpawnNode = NodeManager->GetFirstUnoccupiedNode();
	if (SpawnNode == nullptr || SpawnedUnits[UnitIndex]->GetCost() > Currency)
	{
		return false;
	}

	AvailableUnits[UnitIndex] = nullptr;
	AUnit* SpawnedUnit = SpawnedUnits[UnitIndex];

	SpawnedUnit->SetCurrentNode(SpawnNode);
	SpawnedUnit->SetActorLocation(SpawnNode->GetActorLocation());
	SpawnedUnit->SetIsBought(true);

	Currency -= SpawnedUnit->GetCost();
	Player->AddUnitToOwnedUnits(SpawnedUnit);

	return true;
}

void AUnitShop::SetCurrency(int newAmount)
{
	Currency = newAmount;
}

int AUnitShop::GetCurrency()
{
	return Currency;
}

int AUnitShop::GetStartCurrency()
{
	return StartCurrency;
}

void AUnitShop::AddCurrency(int CurrencyAdded)
{
	Currency += CurrencyAdded;
}

void AUnitShop::SellUnit(AUnit* SellUnit)
{
	Player->RemoveUnitFromOwnedUnits(SellUnit);
	SellUnit->Destroy();
	AddCurrency(SellUnit->GetCost());
}

AUnit* AUnitShop::GetUnitAtIndex(int UnitIndex)
{
	return SpawnedUnits[UnitIndex];
}

