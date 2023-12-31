// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Ranged.generated.h"

UCLASS()
class AUTOCHESS2_API ARanged : public AUnit
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;
	
public:	
	// Sets default values for this actor's properties
	ARanged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Attack() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
