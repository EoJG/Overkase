// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_OctopusSushi.h"

AEO_OctopusSushi::AEO_OctopusSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("OctopusSushi"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/FBX/Food/SF_Octorpus_Sushi.SF_Octorpus_Sushi'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -20));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}

void AEO_OctopusSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
