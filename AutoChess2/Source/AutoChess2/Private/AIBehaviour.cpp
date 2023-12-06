// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviour.h"

// Sets default values for this component's properties
UAIBehaviour::UAIBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIBehaviour::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIBehaviour::SetStats(UUnitStats* NewStats)
{
	UnitStats = NewStats;
}


