// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ReturnPlate.h"


AEO_ReturnPlate::AEO_ReturnPlate()
{
	Tags[0] = TEXT("ReturnPlate");

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Interior/Dishoutlet.Dishoutlet'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	ConstructorHelpers::FClassFinder<AEO_Plate> plateTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Plates.BP_Plates_C'"));
	if (plateTemp.Succeeded())
	{
		rPlate = plateTemp.Class;
	}
}

void AEO_ReturnPlate::OnItem(class AActor* item)
{

}

void AEO_ReturnPlate::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		if (plateCount <= 0)
			bOnItem = false;
	}
}

void AEO_ReturnPlate::SpawnPlate()
{
	AEO_Plate* plateTemp = GetWorld()->SpawnActor<AEO_Plate>(rPlate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation());
	plateTemp->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	plateTemp->bDirty = true;
	plateCount++;

	bOnItem = true;
}
