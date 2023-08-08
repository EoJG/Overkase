// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Octopus.h"

AEO_Octopus::AEO_Octopus()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Octopus"));
}

void AEO_Octopus::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
}
