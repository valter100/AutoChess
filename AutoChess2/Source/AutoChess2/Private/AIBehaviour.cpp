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
	if (!CurrentTarget)
	{
		Attacking = false;
		Moving = false;
		Target();
	}

	if (CurrentTarget != nullptr)
	{
		if (CurrentTarget->GetDead())
		{
			RemoveCurrentTargetFromList();
			return;
		}

		Move();

		if (FVector::Distance(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation()) < UnitStats->GetAttackRange() && TimeSinceLastAttack > 1 / UnitStats->GetAttacksPerSecond())
		{
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

	FVector TargetLocation = CurrentTarget->GetActorLocation();

	float Distance = FVector::Distance(GetOwner()->GetActorLocation(), TargetLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);

	FVector Direction = TargetLocation - GetOwner()->GetActorLocation();
	Direction.Normalize();

	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	FRotator NewRotation = FMath::RInterpTo(GetOwner()->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	GetOwner()->SetActorRotation(NewRotation);
	// Move the actor towards the target
	if (Distance < UnitStats->GetAttackRange())
	{
		Moving = false;
		return;
	}

	FVector NewLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * UnitStats->GetMovementSpeed());
	GetOwner()->SetActorLocation(NewLocation);
	Moving = true;
}

void UAIBehaviour::Attack()
{
	Addon::Print("NORMAL ATTACK");

	CurrentTarget->GetBehaviour()->TakeDamage(UnitStats->GetDamage());
	TimeSinceLastAttack = 0;
	Attacking = true;
	UnitStats->ChangeCurrentMana(UnitStats->GetManaPerHit());

	if (CurrentTarget->GetHealth() <= 0)
	{
		Attacking = false;
		RemoveCurrentTargetFromList();
	}
}

void UAIBehaviour::UseAbility()
{
	Addon::Print("Ability Used!");
	UnitStats->SetCurrentMana(0);
	TimeSinceLastAttack = 0;
}

void UAIBehaviour::TakeDamage(int DamageTaken)
{
	UnitStats->ChangeCurrentHealth(-DamageTaken);

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


