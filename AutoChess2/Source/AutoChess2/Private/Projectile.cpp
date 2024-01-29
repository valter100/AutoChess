// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	TimeAlive += DeltaTime;

	if (Target->GetDead() || TimeAlive >= LifeTime)
	{
		Destroy();
	}

	Super::Tick(DeltaTime);

	Move();

	float DistanceToTarget = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	if (DistanceToTarget < 10)
	{
		Target->ReceiveDamage(Damage);
		Destroy();
	}
}

void AProjectile::SetTarget(AUnit* NewTarget)
{
	Target = NewTarget;
}

void AProjectile::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

void AProjectile::Move()
{
	FVector TargetLocation = Target->GetActorLocation();

	FVector Direction = TargetLocation - GetActorLocation();
	Direction.Normalize();

	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	SetActorRotation(NewRotation);

	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MovementSpeed);
	SetActorLocation(NewLocation);
}

