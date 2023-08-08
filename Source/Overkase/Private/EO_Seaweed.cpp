// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Seaweed.h"

AEO_Seaweed::AEO_Seaweed()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Seaweed"));
}

void AEO_Seaweed::BeginPlay()
{
	Super::BeginPlay();

	bIsCooked = true;
}
