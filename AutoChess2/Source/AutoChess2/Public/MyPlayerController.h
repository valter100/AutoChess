// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <PlacementNode.h>
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AUTOCHESS2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void PlayerTick(float DeltaTime) override;
	void CursorTrace();

	APlacementNode* LastNode;
	APlacementNode* CurrentNode;
};
