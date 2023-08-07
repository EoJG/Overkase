// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Rice.h"

AEO_Rice::AEO_Rice()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Rice"));
}

void AEO_Rice::BeginPlay()
{
	Super::BeginPlay();

	weight = 1;
}
