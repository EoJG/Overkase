// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Seaweed.h"

AEO_Seaweed::AEO_Seaweed()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Seaweed"));

	boxComp->SetBoxExtent(FVector(32, 32, 5));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Food_/SF_Plated_Seaweed.SF_Plated_Seaweed'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -4));
	}
}

void AEO_Seaweed::BeginPlay()
{
	Super::BeginPlay();

	bIsCooked = true;
}
