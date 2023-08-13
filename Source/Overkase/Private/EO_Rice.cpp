// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Rice.h"
#include <Components/BoxComponent.h>

AEO_Rice::AEO_Rice()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Rice"));

	boxComp->SetBoxExtent(FVector(32, 32, 8));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_rice.SF_rice'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -8));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/00/Food/SF_Rice_boiled.SF_Rice_boiled'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -8));
		changeMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}

void AEO_Rice::BeginPlay()
{
	Super::BeginPlay();

	bCanBoil = true;
	coolTime = 3;
}
