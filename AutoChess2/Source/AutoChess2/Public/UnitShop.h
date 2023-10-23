// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "GameFramework/Actor.h"
#include "UnitShop.generated.h"

UCLASS()
class AUTOCHESS2_API AUnitShop : public AActor
{
	GENERATED_BODY()
	
public:	
	TArray <TSharedPtr<AUnit>> AvailableUnits;

	// Sets default values for this actor's properties
	AUnitShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
