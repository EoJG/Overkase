// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Fish.h"
#include <Components/BoxComponent.h>

AEO_Fish::AEO_Fish()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Fish"));
}

void AEO_Fish::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
	coolTime = 3;
}
