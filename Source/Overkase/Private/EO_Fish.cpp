// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Fish.h"
#include <Components/BoxComponent.h>

AEO_Fish::AEO_Fish()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Fish"));

	boxComp->SetBoxExtent(FVector(40, 30, 10));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF__Fish.SF__Fish'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -12));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/00/Food/SF_Slice_Fish1.SF_Slice_Fish1'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -12));
		changeMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> platedMeshTemp(TEXT("'/Game/00/Food/SF_Slice_Fish2.SF_Slice_Fish2'"));
	if (platedMeshTemp.Succeeded())
	{
		platedMeshComp->SetStaticMesh(platedMeshTemp.Object);
		platedMeshComp->SetRelativeLocation(FVector(0, 0, -20));
	}
}

void AEO_Fish::BeginPlay()
{
	Super::BeginPlay();

	bIsOrigin = true;
	bCanChop = true;
	coolTime = 3;
}
