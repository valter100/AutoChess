// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::AddUnitToOwnedUnits(AUnit* NewUnit)
{
	OwnedUnits.Add(NewUnit);
}

void AMyPlayer::RemoveUnitFromOwnedUnits(AUnit* RemovedUnit)
{
	OwnedUnits.Remove(RemovedUnit);
}

void AMyPlayer::ActivateUnits()
{
	for (AUnit* Unit : OwnedUnits)
	{
		if (Unit->GetOnBoard())
		{
			Unit->SetActive(true);
		}
	}
}

TArray<AUnit*> AMyPlayer::GetOwnedUnits()
{
	return OwnedUnits;
}

void AMyPlayer::SetOpponentUnits(TArray<AUnit*> Units)
{
	for (AUnit* Unit : OwnedUnits)
	{
		Unit->SetOpponentUnits(Units);
	}
}

TArray<AUnit*> AMyPlayer::GetUnitsOnBoard()
{
	TArray<AUnit*> UnitsOnBoard;
	for (AUnit* Unit : OwnedUnits)
	{
		if (Unit->GetOnBoard())
		{
			UnitsOnBoard.Add(Unit);
		}
	}

	return UnitsOnBoard;
}

bool AMyPlayer::HasRemainingUnitsOnBoard()
{
	TArray<AUnit*> UnitsOnBoard;
	for (AUnit* Unit : OwnedUnits)
	{
		if (Unit->GetOnBoard() && !Unit->GetDead())
		{
			UnitsOnBoard.Add(Unit);
		}
	}

	return UnitsOnBoard.Num() > 0;
}

void AMyPlayer::ResetUnitsOnBoard()
{
	for (AUnit* Unit : GetUnitsOnBoard())
	{
		Unit->ResetOnBoard();
		Unit->SetActive(false);
	}
}

