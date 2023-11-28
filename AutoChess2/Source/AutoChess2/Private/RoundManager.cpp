// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ARoundManager::ARoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoundManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundShops;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitShop::StaticClass(), FoundShops);


	Shop = Cast<AUnitShop>(FoundShops[0]);
	
}

// Called every frame
void ARoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoundManager::SetShop(AUnitShop* newShop)
{
	Shop = newShop;
}

float ARoundManager::GetRoundTimer()
{
	return RoundTimer;
}

float ARoundManager::GetTimeLeft()
{
	return TimeBetweenRounds - RoundTimer;
}

void ARoundManager::SetRoundTimer(float value)
{
	RoundTimer = value;
}

float ARoundManager::GetTimeBetweenRounds()
{
	return TimeBetweenRounds;
}

void ARoundManager::SetTimeBetweenRounds(float NewValue)
{
	TimeBetweenRounds = NewValue;
}

