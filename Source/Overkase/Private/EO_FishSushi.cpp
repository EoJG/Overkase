// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FishSushi.h"

AEO_FishSushi::AEO_FishSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("FishSushi"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_Sushi_Fish.SF_Sushi_Fish'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -20));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}

void AEO_FishSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
