// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "GameFramework/Actor.h"
#include "Ranged.generated.h"

UCLASS()
class AUTOCHESS2_API ARanged : public AUnit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARanged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
