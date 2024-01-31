// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitStats.h"
#include "MeleeUnitStats.generated.h"

/**
 * 
 */

// Create a new stat component for each new Unit make sure it is BlueprintSpawnableComponent and inherits from UUnitStats
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AUTOCHESS2_API UMeleeUnitStats : public UUnitStats
{
	GENERATED_BODY()
	
};
