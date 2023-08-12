// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Sink.h"

AEO_Sink::AEO_Sink()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("Sink");

	boxComp->SetBoxExtent(FVector(50, 100, 30));

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Interior/S_Sink.S_Sink'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp->SetRelativeLocation(FVector(0, -50, 50));

	ConstructorHelpers::FClassFinder<AEO_Plate> pTemp(TEXT("'/Game/Models/Probs/02/plate.plate'"));
	if (pTemp.Succeeded())
	{
		plate = pTemp.Class;
	}
}

void AEO_Sink::BeginPlay()
{
	Super::BeginPlay();

	bIsInterObj = true;
}

void AEO_Sink::OnItem(class AActor* item)
{

	if (AEO_Plate* plateTemp = Cast<AEO_Plate>(item))
	{
		if (plateTemp->bDirty)
		{
			item->Destroy();
			plateCount++;
		}
	}
}

void AEO_Sink::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		plateCount--;

		if (plateCount <= 0)
			bOnItem = false;
	}
}

void AEO_Sink::Interaction()
{
	if (plateCount > 0)
	{
		curTime += GetWorld()->DeltaTimeSeconds;
		if (curTime >= coolTime)
		{
			SpawnPlate();
			plateCount--;
			curTime = 0;
		}
	}
} 

void AEO_Sink::SpawnPlate()
{
	GetWorld()->SpawnActor<AEO_Plate>(plate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
