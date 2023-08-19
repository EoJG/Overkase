// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_RiceAndCucumber.h"

AEO_RiceAndCucumber::AEO_RiceAndCucumber()
{
	Tags.Add(TEXT("RiceAndCucumber"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_rice_cucumber.SF_rice_cucumber'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -15));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}
