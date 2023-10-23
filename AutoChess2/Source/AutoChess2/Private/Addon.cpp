// Fill out your copyright notice in the Description page of Project Settings.


#include "Addon.h"

Addon::Addon()
{
}

Addon::~Addon()
{
}

void Addon::Print(FString text)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}
