// Fill out your copyright notice in the Description page of Project Settings.


#include "MyOpponent.h"


// Sets default values
AMyOpponent::AMyOpponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyOpponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyOpponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyOpponent::GenerateTeam()
{
	int PlayerUnitAmount = Player->GetUnitsOnBoard().Num();

	for (int i = 0; i < PlayerUnitAmount; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, AllUnits.Num() - 1);
		RandomizedTeam.Add(AllUnits[RandomIndex]);
	}

	SpawnUnits();
}

void AMyOpponent::SpawnUnits()
{

	for (UClass* i : RandomizedTeam)
	{
		SpawnedUnits.Add(GetWorld()->SpawnActor<AUnit>(i));
	}


	for (AUnit* i : SpawnedUnits)
	{
		APlacementNode* Node = nullptr;

		if (i->IsA<AMelee>())
		{
			Node = GetUnnocupiedNode(FrontLine);

			if (Node == nullptr)
			{
				Node = GetUnnocupiedNode(BackLine);
			}
		}
		else if(i->IsA<ARanged>())
		{
			Node = GetUnnocupiedNode(BackLine);

			if (Node == nullptr)
			{
				Node = GetUnnocupiedNode(FrontLine);
			}
		}

		if (Node == nullptr)
			return;

		FVector spawnPosition = Node->GetActorLocation();
		i->SetActorLocation(spawnPosition);
		i->SetOnBoard(true);
		i->SetCurrentNode(Node); //Change to depend on stat changes and rarity
	}
}

void AMyOpponent::CleanUpUnits()
{
	for (TSubclassOf<AUnit> Unit : RandomizedTeam)
	{
		if (Unit)
		{
			Unit = nullptr; // Set the pointer to null to avoid dangling references
		}
	}

	RandomizedTeam.Empty();

	for (AUnit* Unit : SpawnedUnits)
	{
		if (Unit)
		{
			Unit->Destroy(); // Destroy the object
			Unit = nullptr; // Set the pointer to null to avoid dangling references
		}
	}

	SpawnedUnits.Empty();

	for (APlacementNode* Node : FrontLine)
	{
		Node->SetOccupied(false);
	}

	for (APlacementNode* Node : BackLine)
	{
		Node->SetOccupied(false);
	}
}

APlacementNode* AMyOpponent::GetUnnocupiedNode(TArray<APlacementNode*> NodeArray)
{
	for (APlacementNode* i : NodeArray)
	{
		if (i->GetOccupied() == false)
			return i;
	}

	return nullptr;
}

void AMyOpponent::ActivateUnits()
{
	for (AUnit* Unit : SpawnedUnits)
	{
		Unit->SetActive(true);
	}
}

void AMyOpponent::SetOpponentUnits(TArray<AUnit*> Units)
{
	for (AUnit* Unit : SpawnedUnits)
	{
		Unit->SetOpponentUnits(Units);
	}
}

TArray<AUnit*> AMyOpponent::GetSpawnedUnits()
{
	return SpawnedUnits;
}

bool AMyOpponent::HasRemainingUnitsOnBoard()
{
	TArray<AUnit*> UnitsOnBoard;
	for (AUnit* Unit : SpawnedUnits)
	{
		if (Unit->GetOnBoard() && !Unit->GetDead())
		{
			UnitsOnBoard.Add(Unit);
		}
	}

	return UnitsOnBoard.Num() > 0;
}



