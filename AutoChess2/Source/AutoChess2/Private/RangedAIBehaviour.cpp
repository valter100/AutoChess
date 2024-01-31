// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAIBehaviour.h"
#include "Addon.h"

// Overloaded function of the AIBehaviour's attack function
void URangedAIBehaviour::Attack()
{
	TimeSinceLastAttack = 0;
	UnitStats->ChangeCurrentMana(UnitStats->GetManaPerHit());
	Attacking = true;

	if (CurrentTarget->GetHealth() <= 0)
	{
		Attacking = false;
		RemoveCurrentTargetFromList();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	// Spawn the projectile at the muzzle.
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (Projectile)
	{
		Projectile->SetDamage(UnitStats->GetDamage());
		Projectile->SetTarget(CurrentTarget);
	}
}
