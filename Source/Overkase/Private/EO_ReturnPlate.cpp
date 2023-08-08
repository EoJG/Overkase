// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ReturnPlate.h"


AEO_ReturnPlate::AEO_ReturnPlate()
{
	Tags[0] = TEXT("ReturnPlate");

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/Dishoutlet_Dishoutlet.Dishoutlet_Dishoutlet'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	ConstructorHelpers::FClassFinder<AEO_Plate> plateTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Plate.BP_Plate_C'"));
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
		bOnItem = false;
	}
}

void AEO_ReturnPlate::SpawnPlate()
{
	GetWorld()->SpawnActor<AEO_Plate>(rPlate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	bOnItem = true;
}
