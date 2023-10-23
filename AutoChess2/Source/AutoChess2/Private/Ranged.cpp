// Fill out your copyright notice in the Description page of Project Settings.


#include "Ranged.h"

// Sets default values
ARanged::ARanged()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARanged::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

