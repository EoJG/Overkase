// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Stove.h"
#include "EO_Food.h"
#include "EO_Pot.h"

AEO_Stove::AEO_Stove()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("Stove");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/Models/Re/Interior/S_Stove_Stove.S_Stove_Stove'"));
	if (MeshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(MeshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -45));
	}
}

void AEO_Stove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanCook)
	{
		sFoodTemp->curTime += DeltaTime;
		progressWidget->curTime = sFoodTemp->curTime;
		if (sFoodTemp->curTime >= sFoodTemp->coolTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("IsCoocked"), sFoodTemp->curTime);
			sFoodTemp->bIsCooked = true;
			widgetComp->SetVisibility(false);
		}
		else
		{
			widgetComp->SetVisibility(true);
			progressWidget->BindProgressFunc();
		}
	}
}

void AEO_Stove::OnItem(class AActor* item)
{
	if (!bOnItem)
	{
		if (AEO_Pot* potItem = Cast<AEO_Pot>(item))
		{
			if (potItem->bInFood)
			{
				TArray<AActor*> items;
				potItem->GetAttachedActors(items);
				sFoodTemp = Cast<AEO_Food>(items[0]);
				progressWidget->coolTime = sFoodTemp->coolTime;

				bCanCook = true;
			}
		}

		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

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

					sFoodTemp = pFood;
					progressWidget->coolTime = sFoodTemp->coolTime;
					potTemp->bInFood = true;
					bCanCook = true;
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
					progressWidget->coolTime = sFoodTemp->coolTime;

					pPot->bInFood = true;
					bCanCook = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}

void AEO_Stove::GetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	sFoodTemp = nullptr;
	bCanCook = false;
}