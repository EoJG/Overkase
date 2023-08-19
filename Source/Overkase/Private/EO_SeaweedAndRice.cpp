// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_SeaweedAndRice.h"

AEO_SeaweedAndRice::AEO_SeaweedAndRice()
{
	Tags.Add(TEXT("SeaweedAndRice"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Food/SF_Seaweed_rice.SF_Seaweed_rice'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -15));
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
}
