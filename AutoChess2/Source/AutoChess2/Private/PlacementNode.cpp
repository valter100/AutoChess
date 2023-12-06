// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementNode.h"

// Sets default values
APlacementNode::APlacementNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlacementNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlacementNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlacementNode::SetOccupied(bool state)
{
	Occupied = state;
}

bool APlacementNode::GetOccupied()
{
	return Occupied;
}

void APlacementNode::HighlightNode()
{
	Addon::Print("SCALING UP");
	SetActorScale3D(HoveredScale);
}

void APlacementNode::UnhighlightNode()
{
	Addon::Print("SCALING DOWN");
	SetActorScale3D(NormalScale);
}

//void APlacementNode::SellUnit(AUnit* SellUnit)
//{
//	Shop->SellUnit(SellUnit);
//}

