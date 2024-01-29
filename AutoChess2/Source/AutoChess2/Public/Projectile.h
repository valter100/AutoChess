// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Unit.h>
#include "AIBehaviour.h"
#include "Projectile.generated.h"

UCLASS()
class AUTOCHESS2_API AProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	AUnit* Target;
	float Damage;

	UPROPERTY(EditAnywhere)
	float LifeTime;
	float TimeAlive;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTarget(AUnit* NewTarget);
	void SetDamage(float NewDamage);
	void Move();
};
