// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnit::Die()
{
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

}

void AUnit::SetPickedUp(bool state)
{
	PickedUp = state;
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
}

void AUnit::Lift()
{
	if (CurrentNode)
	{
		LastNode = CurrentNode;
		CurrentNode = nullptr;
	}
}

FText AUnit::statData()
{
	return FText::FromString("Name: " + Name + "\n" + "Health: ");/* + Health*//* + "\n" +
		"Damage: " Damage;*/
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

