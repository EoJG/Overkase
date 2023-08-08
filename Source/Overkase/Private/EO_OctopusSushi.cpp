// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_OctopusSushi.h"

AEO_OctopusSushi::AEO_OctopusSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("OctopusSushi"));
}

void AEO_OctopusSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
