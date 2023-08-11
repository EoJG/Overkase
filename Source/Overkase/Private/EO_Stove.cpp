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
		foodTemp->curTime += DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("%f"), foodTemp->curTime);
		if (foodTemp->curTime >= foodTemp->coolTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("IsCoocked"), foodTemp->curTime);
			foodTemp->bIsCooked = true;
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
				foodTemp = Cast<AEO_Food>(items[0]);

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
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (!plateTemp->bDirty)
			{
				if (AEO_Pot* potTemp = Cast<AEO_Pot>(item))
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);
					}
				}
				else
				{
					if (!plateTemp->CheckOnFood(Cast<AEO_Food>(item)->Tags[0]))
					{
						item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

						plateTemp->CheckRecipe(item->Tags[0]);
					}
				}
			}
		}
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (Cast<AEO_Food>(item)->bCanBoil && !potTemp->bInFood)
			{
				item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				foodTemp = Cast<AEO_Food>(item);
				foodTemp->meshComp->SetVisibility(false);

				potTemp->bInFood = true;
				bCanCook = true;
			}
		}
		else if (AEO_Plate* pPlateTemp = Cast<AEO_Plate>(item))
		{
			if (!plateTemp->bDirty)
			{
				if (!pPlateTemp->CheckOnFood(Cast<AEO_Food>(items[0])->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					items[0]->AttachToComponent(pPlateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					pPlateTemp->CheckRecipe(items[0]->Tags[0]);
				}
			}
		}
		else if (AEO_Pot* pPotTemp = Cast<AEO_Pot>(item))
		{
			if (Cast<AEO_Food>(item)->bCanBoil && !pPotTemp->bInFood)
			{
				item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				items[0]->AttachToActor(pPotTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				foodTemp = Cast<AEO_Food>(items[0]);
				foodTemp->meshComp->SetVisibility(false);

				pPotTemp->bInFood = true;
				bCanCook = true;
			}
		}
	}
}

void AEO_Stove::GetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	foodTemp = nullptr;
	bCanCook = false;
}