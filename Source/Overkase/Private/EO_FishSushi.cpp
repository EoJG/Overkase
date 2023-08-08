// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FishSushi.h"

AEO_FishSushi::AEO_FishSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("FishSushi"));
}

void AEO_FishSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
