// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Octopus.h"
#include <Components/BoxComponent.h>


AEO_Octopus::AEO_Octopus()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Octopus"));

	boxComp->SetBoxExtent(FVector(32, 20, 13));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/FBX/Food/SF_Octorpus.SF_Octorpus'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, -10, -12));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/FBX/Food/SF_Slice_Octorpus.SF_Slice_Octorpus'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -10));
		changeMeshComp->SetRelativeRotation(FRotator(0, 100, 0));
	}
}

void AEO_Octopus::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
	coolTime = 3;
}
