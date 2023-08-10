// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Octopus.h"

AEO_Octopus::AEO_Octopus()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Octopus"));

	boxComp->SetBoxExtent(FVector(32, 20, 13));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/02/Octorpus.Octorpus'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, -10, -12));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/Models/Probs/02/Slice_Octorpus.Slice_Octorpus'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(-25, 0, -10));
		changeMeshComp->SetRelativeRotation(FRotator(0, 100, 0));
	}
}

void AEO_Octopus::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
	coolTime = 3;
}
