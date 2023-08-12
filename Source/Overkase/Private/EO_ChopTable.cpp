// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ChopTable.h"
#include "../Public/EO_Food.h"
#include "EO_NonePlate.h"
#include "EO_Progressbar.h"

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
			progressWidget->coolTime = food->coolTime;
		}	

		bOnItem = true;
	}
	else
	{
		TArray<AActor*> items;
		GetAttachedActors(items);
		// 테이블 위에 아이템이 접시 일 때
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				return;
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (!plateTemp->bDirty && pPot->bInFood)
				{
					TArray<AActor*> inFoods;
					pPot->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						plateTemp->CheckRecipe(inFoods[0]->Tags[0]);
						pPot->bInFood = false;
					}
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (!plateTemp->CheckOnFood(pFood->Tags[0]))
				{
					item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					plateTemp->CheckRecipe(item->Tags[0]);
				}
			}
		}
		// 테이블 위에 아이템이 냄비 일 때
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && potTemp->bInFood)
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						pPlate->CheckRecipe(inFoods[0]->Tags[0]);
						potTemp->bInFood = false;
					}
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				return;
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (pFood->bCanBoil && !potTemp->bInFood)
				{
					item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

					potTemp->bInFood = true;
				}
			}
		}
		// 테이블 위에 아이템이 음식 일 때
		else if (AEO_Food* foodTemp = Cast<AEO_Food>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && !pPlate->CheckOnFood(foodTemp->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					pPlate->CheckRecipe(foodTemp->Tags[0]);
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (foodTemp->bCanBoil && !pPot->bInFood)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToActor(pPot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->meshComp->SetVisibility(false);

					pPot->bInFood = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}

void AEO_ChopTable::Interaction()
{
	if (bOnItem && !food->bIsCooked && food->bCanChop)
	{
		food->curTime += GetWorld()->GetDeltaSeconds();
		progressWidget->curTime = food->curTime;
		if (food->curTime >= food->coolTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("Maked"));
			food->bIsCooked = true;
			food->changeMeshComp->SetVisibility(true);
			food->meshComp->SetVisibility(false);
			widgetComp->SetVisibility(false);
		}
		else
		{
			widgetComp->SetVisibility(true);
			progressWidget->BindProgressFunc();
		}
	}
}
