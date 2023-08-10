// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ChopTable.h"
#include "../Public/EO_Food.h"
#include "EO_NonePlate.h"

AEO_ChopTable::AEO_ChopTable()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("ChopTable");
}

void AEO_ChopTable::BeginPlay()
{
	Super::BeginPlay();

	bIsInterObj = true;
}

void AEO_ChopTable::OnItem(class AActor* item)
{
	if (!bOnItem)
	{
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		TArray<AActor*> child;
		GetAttachedActors(child);

		if (AEO_Food* temp = Cast<AEO_Food>(child[0]))
		{
			food = temp;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *food->GetName());
		}

		bOnItem = true;
	}
	else
	{
		TArray<AActor*> items;
		GetAttachedActors(items);
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			plateTemp->CheckRecipe(item->Tags[0]);
		}
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

			potTemp->bInFood = true;
		}
		else if (AEO_Plate* pPlateTemp = Cast<AEO_Plate>(item))
		{
			item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			items[0]->AttachToComponent(pPlateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			pPlateTemp->CheckRecipe(items[0]->Tags[0]);
		}
		else if (AEO_Pot* pPotTemp = Cast<AEO_Pot>(item))
		{
			item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			items[0]->AttachToActor(pPotTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Cast<AEO_Food>(items[0])->meshComp->SetVisibility(false);

			pPotTemp->bInFood = true;
		}
	}
}

void AEO_ChopTable::Interaction()
{
	if (bOnItem && !food->bIsCooked && food->bCanChop)
	{
		food->curTime += GetWorld()->GetDeltaSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%.2f"), food->curTime);
		if (food->curTime >= food->coolTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("Maked"));
			food->bIsCooked = true;
			food->changeMeshComp->SetVisibility(true);
			food->meshComp->SetVisibility(false);
		}
	}
}
