// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "GameFramework/Actor.h"
#include "PlacementNode.generated.h"

UCLASS()
class AUTOCHESS2_API APlacementNode : public AActor
{
	GENERATED_BODY()
	
public:	
	TSharedPtr<AUnit> currentUnit;

	// Sets default values for this actor's properties
	APlacementNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
