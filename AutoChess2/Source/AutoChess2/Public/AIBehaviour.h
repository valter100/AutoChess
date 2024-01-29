// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Unit.h"
#include "AIBehaviour.generated.h"

class AUnit;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOCHESS2_API UAIBehaviour : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehaviour();
	UUnitStats* UnitStats;
	AUnit* CurrentTarget;
	bool Dead;
	bool Attacking;
	bool Moving;
	float TimeSinceLastAttack;
	TArray<AUnit*> OpponentUnits;
	APlacementNode* CurrentNode;

	void DecideBehaviour();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Target();
	virtual void Move(); 
	virtual void Attack();
	virtual void UseAbility();
	virtual void Die();
	virtual void RemoveCurrentTargetFromList();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDamagedEffect(FVector HitLocation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void TakeDamage(int DamageTaken);
	bool IsDead();
	bool IsMoving();
	bool IsAttacking();
	void Reset();
	void SetOpponentUnits(TArray<AUnit*> Units);
	void SetStats(UUnitStats* NewStats);
	void SetCurrentNode(APlacementNode* NewNode);
};
