// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_CucumberSushi.h"

AEO_CucumberSushi::AEO_CucumberSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("CucumberSushi"));
}

void AEO_CucumberSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
