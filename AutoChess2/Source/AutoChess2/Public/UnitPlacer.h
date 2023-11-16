// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "NodeManager.h"
#include "GameFramework/Actor.h"
#include "UnitPlacer.generated.h"

UCLASS()
class AUTOCHESS2_API AUnitPlacer : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	AUnit* PickedUpUnit;
	// Sets default values for this actor's properties
	AUnitPlacer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, category = "Unit Placer")
	void SetPickedUpUnit(AUnit* newUnit);	
	UFUNCTION(BlueprintCallable, category = "Unit Placer")
	void SetPickedUpUnitToNull();
	UFUNCTION(BlueprintPure, category = "Unit Placer")
	AUnit* GetPickedUpUnit();
};
