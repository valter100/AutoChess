// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"

// Sets default values
AUnit::AUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UnitStats = FindComponentByClass<UUnitStats>();
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	stats = FindComponentByClass<UUnitStats>();

	IncreasedStat = stats->IncreaseRandomStat();
	DecreasedStat = stats->DecreaseRandomStat();

	stats->SetCurrentHealth(stats->GetMaxHealth());
}

void AUnit::Die()
{
	SetActorHiddenInGame(true);
	Dead = true;
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PickedUp)
	{
		MoveToMouse();
		return;
	}

	if (!OnBoard || Dead || !Active)
		return;

	TimeSinceLastAttack += DeltaTime;

	if (!CurrentTarget)
	{
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

		if (FVector::Distance(GetActorLocation(), CurrentTarget->GetActorLocation()) < stats->GetAttackRange() && TimeSinceLastAttack > 1 / stats->GetAttacksPerSecond())
		{
			if (stats->GetCurrentMana() >= stats->GetMaxMana())
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

void AUnit::SetPickedUp(bool state)
{
	PickedUp = state;
}

bool AUnit::GetPickedUp()
{
	return PickedUp;
}

void AUnit::TogglePickedUp()
{
	PickedUp = !PickedUp;

	if (!PickedUp)
	{
		Place();
	}
	else
	{
		Lift();
	}
}

void AUnit::MoveToMouse()
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	float TraceDistance = 2000;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	float MouseX, MouseY;
	FVector WorldLocation, WorldDirection;
	PlayerController->GetMousePosition(MouseX, MouseY);
	PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * TraceDistance, ECC_Visibility, CollisionParams))
	{
		if (HitResult.GetActor()->ActorHasTag("Ground"))
		{
			SetActorLocation(HitResult.ImpactPoint);
			HoveredNode = nullptr;
		}

		else if (HitResult.GetActor()->ActorHasTag("Node"))
		{
			SetActorLocation(HitResult.GetActor()->GetActorLocation());
			HoveredNode = Cast<APlacementNode>(HitResult.GetActor());
		}
	}
}

void AUnit::Place()
{
	if (HoveredNode)
	{
		CurrentNode = HoveredNode;
		HoveredNode = nullptr;
	}
	else
	{
		CurrentNode = LastNode;
		SetActorLocation(CurrentNode->GetActorLocation());
	}

	CurrentNode->SetOccupied(true);

	if (CurrentNode->ActorHasTag("Sideline"))
	{
		SetOnBoard(false);
	}
	else if (CurrentNode->ActorHasTag("Battle"))
	{
		SetOnBoard(true);
	}
	else if (CurrentNode->ActorHasTag("Sell"))
	{
		Sell = true;
	}
}

void AUnit::Lift()
{
	if (CurrentNode)
	{
		LastNode = CurrentNode;
		CurrentNode->SetOccupied(false);
		CurrentNode = nullptr;
	}
}

void AUnit::Move()
{
	if (!CurrentTarget)
		return;

	FVector TargetLocation = CurrentTarget->GetActorLocation();

	float Distance = FVector::Distance(GetActorLocation(), TargetLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
	if (Distance < stats->GetAttackRange())
		return;

	FVector Direction = TargetLocation - GetActorLocation();
	Direction.Normalize();

	AddActorLocalOffset(Direction * stats->GetMovementSpeed());
}

void AUnit::Target()
{
	float ClosestDistance = FLT_MAX;
	AUnit* ClosestUnit = nullptr;

	for (int i = 0; i < OpponentUnits.Num(); i++)
	{
		if (OpponentUnits[i] == nullptr)
			continue;

		float distanceToUnit = FVector::Distance(GetActorLocation(), OpponentUnits[i]->GetActorLocation());

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

void AUnit::Attack()
{
	CurrentTarget->TakeDamage(stats->GetDamage());
	TimeSinceLastAttack = 0;

	stats->ChangeCurrentMana(stats->GetManaPerHit());

	if (CurrentTarget->GetHealth() <= 0)
	{
		RemoveCurrentTargetFromList();
	}
}

void AUnit::UseAbility()
{
	Addon::Print("Ability Used!");
	stats->SetCurrentMana(0);
	TimeSinceLastAttack = 0;
}

void AUnit::TakeDamage(int DamageTaken)
{
	stats->ChangeCurrentHealth(-DamageTaken);

	if(stats->GetCurrentMana() < stats->GetMaxMana())
	{
		stats->ChangeCurrentMana(stats->GetManaWhenHit());
	}

	if (stats->GetCurrentHealth() <= 0)
		Die();
}

void AUnit::RemoveCurrentTargetFromList()
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

int AUnit::GetHealth()
{
	return stats->GetCurrentHealth();
}

float AUnit::GetHealthPercentage()
{
	return float(stats->GetCurrentHealth())/float(stats->GetMaxHealth());
}

float AUnit::GetManaPercentage()
{
	return float(stats->GetCurrentMana()) / float(stats->GetMaxMana());
}

FText AUnit::GetNameOfUnit()
{
	return FText::FromString(stats->GetName());
}

FText AUnit::statData()
{
	return FText::FromString("Cost: " + FString::FromInt(Cost) + "\n" + 
		"Health: " + FString::SanitizeFloat(stats->GetMaxHealth()) + "\n" +
		"Damage: " + FString::SanitizeFloat(stats->GetDamage()) + "\n" +
		"Attack Speed: " + FString::SanitizeFloat(stats->GetAttacksPerSecond()) + "\n" + +"\n"+ 
		"Increased Stat: " + IncreasedStat + +"\n" + 
		"Decreased Stat: " + DecreasedStat);
}

UTexture2D* AUnit::GetImageTex()
{
	return ImageTexture;
}

bool AUnit::GetIsBought()
{
	return IsBought;
}

void AUnit::SetIsBought(bool State)
{
	IsBought = State;
}

void AUnit::SetCurrentNode(APlacementNode* NewNode)
{
	CurrentNode = NewNode;
	CurrentNode->SetOccupied(true);
}

void AUnit::SetOnBoard(bool state)
{
	OnBoard = state;
}

bool AUnit::GetOnBoard()
{
	return OnBoard;
}

void AUnit::SetActive(bool state)
{
	Active = state;
}

bool AUnit::GetActive()
{
	return Active;
}

void AUnit::SetCost(int NewCost)
{
	Cost = NewCost;
}

int AUnit::GetCost()
{
	return Cost;
}

void AUnit::RandomizeStats()
{

}

bool AUnit::GetDead()
{
	return Dead;
}

void AUnit::SetOpponentUnits(TArray<AUnit*> Units)
{
	OpponentUnits = Units;
}

void AUnit::ResetOnBoard()
{
	stats->SetCurrentHealth(stats->GetMaxHealth());
	stats->SetCurrentMana(0);
	TimeSinceLastAttack = 0;
	Dead = false;
	CurrentTarget = nullptr;
	SetActorLocation(CurrentNode->GetActorLocation());
	SetActorHiddenInGame(false);
}

bool AUnit::GetSell()
{
	return Sell;
}

