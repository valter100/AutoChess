// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::SpawnMosters()
{
	int playerMonsterAmount = 0;

	for (AUnit* Unit : Player->GetOwnedUnits())
	{
		if (Unit->GetOnBoard())
			playerMonsterAmount++;
	}

	for (int i = 0; i < playerMonsterAmount; i++)
	{
		SpawnMonster();
	}
}

void AEnemyManager::SpawnMonster()
{
	int nodeIndex = FMath::RandRange(0, UnoccupiedPlacementNodes.Num());

	APlacementNode* targetNode = UnoccupiedPlacementNodes[nodeIndex];

	OccupiedPlacementNodes.Add(targetNode);
	UnoccupiedPlacementNodes.Remove(targetNode);
	

}

