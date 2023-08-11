// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Fish.h"
#include <Components/BoxComponent.h>

AEO_Fish::AEO_Fish()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Fish"));

	boxComp->SetBoxExtent(FVector(40, 30, 10));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Food_/SF__Fish.SF__Fish'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -12));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/Models/Re/Food_/SF_Slice_Fish.SF_Slice_Fish'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -12));
	}
}

void AEO_Fish::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
	coolTime = 3;
}
