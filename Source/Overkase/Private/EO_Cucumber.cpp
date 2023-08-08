// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Cucumber.h"

AEO_Cucumber::AEO_Cucumber()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Cucumber"));
}

void AEO_Cucumber::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
}
