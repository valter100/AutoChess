// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBehaviour.h"
#include "Projectile.h"
#include "RangedAIBehaviour.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AUTOCHESS2_API URangedAIBehaviour : public UAIBehaviour
{
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	GENERATED_BODY()
	
	virtual void Attack() override;
};
