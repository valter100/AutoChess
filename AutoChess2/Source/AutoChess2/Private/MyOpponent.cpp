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

// Generates a random unit for each unit on the Player team
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

// Places the randomized units onto random nodes, prioritizing front line for Melee and Back line for Ranged units
void AMyOpponent::SpawnUnits()
{

	for (UClass* i : RandomizedTeam)
	{
		SpawnedUnits.Add(GetWorld()->SpawnActor<AUnit>(i));
	}


	for (AUnit* unit : SpawnedUnits)
	{
		APlacementNode* Node = nullptr;

		if (unit->IsA<AMelee>())
		{
			Node = GetRandomUnnocupiedNode(FrontLine);

			if (Node == nullptr)
			{
				Node = GetRandomUnnocupiedNode(BackLine);
			}
		}
		else if(unit->IsA<ARanged>())
		{
			Node = GetRandomUnnocupiedNode(BackLine);

			if (Node == nullptr)
			{
				Node = GetRandomUnnocupiedNode(FrontLine);
			}
		}

		if (Node == nullptr)
			return;

		FVector spawnPosition = Node->GetActorLocation();
		unit->SetActorLocation(spawnPosition);
		unit->SetOnBoard(true);
		unit->SetCurrentNode(Node);
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

APlacementNode* AMyOpponent::GetRandomUnnocupiedNode(TArray<APlacementNode*> NodeArray)
{
	int randomIndex = FMath::RandRange(0, NodeArray.Num() - 1);

	for (APlacementNode* i : NodeArray)
	{
		if (!NodeArray[randomIndex]->GetOccupied())
		{
			return NodeArray[randomIndex];
		}
		else
		{
			randomIndex++;

			if (randomIndex == NodeArray.Num())
			{
				randomIndex = 0;
			}
		}
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



