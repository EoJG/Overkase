// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Rice.h"

AEO_Rice::AEO_Rice()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Rice"));

	boxComp->SetBoxExtent(FVector(32, 32, 8));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Food_/SF_rice.SF_rice'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -8));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/Models/Re/Food_/SF_Rice_boiled.SF_Rice_boiled'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -8));
	}
}

void AEO_Rice::BeginPlay()
{
	Super::BeginPlay();

	bCanBoil = true;
	coolTime = 3;
}
