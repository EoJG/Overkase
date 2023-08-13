// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Cucumber.h"

AEO_Cucumber::AEO_Cucumber()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Cucumber"));

	boxComp->SetBoxExtent(FVector(40, 10, 10));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_Cucumber.SF_Cucumber'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -14));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/00/Food/SF_Slice_Cucumber2.SF_Slice_Cucumber2'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -12));
		changeMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}

void AEO_Cucumber::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
}
