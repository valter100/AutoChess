// Fill out your copyright notice in the Description page of Project Settings.


#include "Ranged.h"
#include <RangedUnitStats.h>

// Sets default values
ARanged::ARanged()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARanged::BeginPlay()
{
	stats = FindComponentByClass<URangedUnitStats>();

	Super::BeginPlay();
}

void ARanged::Attack()
{
	TimeSinceLastAttack = 0;
	stats->ChangeCurrentMana(stats->GetManaPerHit());
	IsAttacking = true;

	if (CurrentTarget->GetHealth() <= 0)
	{
		IsAttacking = false;
		RemoveCurrentTargetFromList();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Spawn the projectile at the muzzle.
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	if (Projectile)
	{
		Projectile->SetDamage(stats->GetDamage());
		Projectile->SetTarget(CurrentTarget);
	}
}

// Called every frame
void ARanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

