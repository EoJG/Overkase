// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Cucumber.h"

AEO_Cucumber::AEO_Cucumber()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Cucumber"));

	boxComp->SetBoxExtent(FVector(40, 10, 10));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Food_/SF__cucumber.SF__cucumber'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -14));
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/Models/Re/Food_/SF_Slice_Cucumber_2.SF_Slice_Cucumber_2'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
		changeMeshComp->SetRelativeLocation(FVector(0, 0, -12));
	}
}

void AEO_Cucumber::BeginPlay()
{
	Super::BeginPlay();

	bCanChop = true;
}
