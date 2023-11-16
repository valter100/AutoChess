// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementNode.h"
#include "GameFramework/Actor.h"
#include "NodeManager.generated.h"

UCLASS()
class AUTOCHESS2_API ANodeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	TArray<APlacementNode*> PlacementNodes;
	UPROPERTY(EditAnywhere)
	TArray<APlacementNode*> SideLineNodes;
	ANodeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	APlacementNode* GetFirstUnoccupiedNode();
	UFUNCTION(BlueprintCallable, category = "Node Manager")
	void TogglePlacementNodes();

};
