// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_RiceAndFish.h"

AEO_RiceAndFish::AEO_RiceAndFish()
{
	Tags.Add(TEXT("RiceAndFish"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_rice_fish.SF_rice_fish'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -15));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}
