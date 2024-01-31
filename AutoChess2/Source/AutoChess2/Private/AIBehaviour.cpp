// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviour.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UAIBehaviour::UAIBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAIBehaviour::DecideBehaviour()
{
	// If there is no target
	if (!CurrentTarget)
	{
		Attacking = false;
		Moving = false;
		Target();
	}

	// If there is a target
	if (CurrentTarget != nullptr)
	{
		// If the target is dead
		if (CurrentTarget->GetDead())
		{
			//Remove the target from targetable enemies list
			RemoveCurrentTargetFromList();
			return;
		}

		// Try to move towards the target
		Move();

		// If target is within range
		if (FVector::Distance(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation()) < UnitStats->GetAttackRange() && TimeSinceLastAttack > 1 / UnitStats->GetAttacksPerSecond())
		{
			// If the units mana is full
			if (UnitStats->GetCurrentMana() >= UnitStats->GetMaxMana())
			{
				UseAbility();
			}
			else
			{
				Attack();
			}
		}
	}
}

// Called when the game starts
void UAIBehaviour::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	TimeSinceLastAttack += DeltaTime;
}

void UAIBehaviour::Target()
{
	float ClosestDistance = FLT_MAX;
	AUnit* ClosestUnit = nullptr;

	// Loop through opponents units and find the one closest to the unit
	for (int i = 0; i < OpponentUnits.Num(); i++)
	{
		if (OpponentUnits[i] == nullptr)
			continue;

		float distanceToUnit = FVector::Distance(GetOwner()->GetActorLocation(), OpponentUnits[i]->GetActorLocation());

		if (distanceToUnit < ClosestDistance)
		{
			ClosestDistance = distanceToUnit;
			ClosestUnit = OpponentUnits[i];
		}
	}

	if (ClosestUnit)
	{
		CurrentTarget = ClosestUnit;
	}
}

bool UAIBehaviour::IsDead()
{
	return Dead;
}

bool UAIBehaviour::IsMoving()
{
	return Moving;
}

bool UAIBehaviour::IsAttacking()
{
	return Attacking;
}

void UAIBehaviour::Reset()
{
	TimeSinceLastAttack = 0;
	Dead = false;
	CurrentTarget = nullptr;
	Attacking = false;
	Moving = false;
}

void UAIBehaviour::SetOpponentUnits(TArray<AUnit*> Units)
{
	OpponentUnits = Units;
}

void UAIBehaviour::SetStats(UUnitStats* NewStats)
{
	UnitStats = NewStats;
}

void UAIBehaviour::SetCurrentNode(APlacementNode* NewNode)
{
	CurrentNode = NewNode;
}

void UAIBehaviour::Move()
{
	if (!CurrentTarget)
	{
		return;
	}

	// Calculate the distance and direction vector towards the current target
	FVector TargetLocation = CurrentTarget->GetActorLocation();
	float Distance = FVector::Distance(GetOwner()->GetActorLocation(), TargetLocation);
	FVector Direction = TargetLocation - GetOwner()->GetActorLocation();
	Direction.Normalize();

	// Rotate the unit towards the current target
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	FRotator NewRotation = FMath::RInterpTo(GetOwner()->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	GetOwner()->SetActorRotation(NewRotation);


	// Cancel movement if unit is within range of target
	if (Distance < UnitStats->GetAttackRange())
	{
		Moving = false;
		return;
	}

	// Perform the movement
	FVector NewLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * UnitStats->GetMovementSpeed());
	GetOwner()->SetActorLocation(NewLocation);
	Moving = true;
}

void UAIBehaviour::Attack()
{
	// Deal damage to the target through their behaviour script
	CurrentTarget->GetBehaviour()->TakeDamage(UnitStats->GetDamage());

	// Increase mana
	UnitStats->ChangeCurrentMana(UnitStats->GetManaPerHit());

	TimeSinceLastAttack = 0;
	Attacking = true;

	// If the targets health is equal to or below zero, remove from target list
	if (CurrentTarget->GetHealth() <= 0)
	{
		Attacking = false;
		RemoveCurrentTargetFromList();
	}
}

void UAIBehaviour::UseAbility()
{
	// Implement ability here //
	UnitStats->SetCurrentMana(0);
	TimeSinceLastAttack = 0;
}

void UAIBehaviour::TakeDamage(int DamageTaken)
{
	UnitStats->ChangeCurrentHealth(-DamageTaken);

	//Trigger the blueprint event
	PlayDamagedEffect(GetOwner()->GetActorLocation());

	if (UnitStats->GetCurrentMana() < UnitStats->GetMaxMana())
	{
		UnitStats->ChangeCurrentMana(UnitStats->GetManaWhenHit());
	}

	if (UnitStats->GetCurrentHealth() <= 0)
		Die();
}

void UAIBehaviour::Die()
{
	GetOwner()->SetActorHiddenInGame(true);
	Dead = true;
}

void UAIBehaviour::RemoveCurrentTargetFromList()
{
	//Loop through all opponent units and move the killed unit to the back of the list and reduce list count by one
	for (int i = 0; i < OpponentUnits.Num(); i++)
	{
		if (OpponentUnits[i] == CurrentTarget)
		{
			CurrentTarget = nullptr;
			OpponentUnits[i] = OpponentUnits[OpponentUnits.Num() - 1];
			OpponentUnits.SetNum(OpponentUnits.Num() - 1);
			return;
		}
	}
}


