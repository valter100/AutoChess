// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AMyPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastNode = CurrentNode;
	CurrentNode = Cast<APlacementNode>(CursorHit.GetActor());

	if (LastNode == nullptr && CurrentNode != nullptr)
	{
		CurrentNode->HighlightNode();
	}
	else if (LastNode != nullptr && CurrentNode == nullptr)
	{
		LastNode->UnhighlightNode();
	}
	else if (LastNode != nullptr && CurrentNode != nullptr && LastNode != CurrentNode)
	{
		LastNode->UnhighlightNode();
		CurrentNode->HighlightNode();
	}
}
