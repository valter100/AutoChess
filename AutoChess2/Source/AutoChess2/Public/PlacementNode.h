// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Addon.h"
#include "PlacementNode.generated.h"

UCLASS()
class AUTOCHESS2_API APlacementNode : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere) bool Occupied;
	UPROPERTY(EditAnywhere) FVector NormalScale;
	UPROPERTY(EditAnywhere) FVector HoveredScale;
	//UPROPERTY(EditAnywhere) AUnitShop* Shop;
	// Sets default values for this actor's properties
	APlacementNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetOccupied(bool state);
	bool GetOccupied();
	void HighlightNode();
	void UnhighlightNode();
	//void SellUnit(AUnit* SellUnit);
};
