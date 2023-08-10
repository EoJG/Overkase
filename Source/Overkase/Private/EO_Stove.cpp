// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Stove.h"
#include "EO_Food.h"
#include "EO_Pot.h"

AEO_Stove::AEO_Stove()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("Stove");

	meshComp->SetRelativeLocation(FVector(0, 0, 50));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/Models/Probs/Stove.Stove'"));
	if (MeshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(MeshTemp.Object);
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
			item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			plateTemp->CheckRecipe(item->Tags[0]);
		}
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			foodTemp = Cast<AEO_Food>(item);
			foodTemp->meshComp->SetVisibility(false);

			potTemp->bInFood = true;
			bCanCook = true;
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
			foodTemp = Cast<AEO_Food>(item);
			foodTemp->meshComp->SetVisibility(false);

			pPotTemp->bInFood = true;
			bCanCook = true;
		}
	}
}

void AEO_Stove::GetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	foodTemp = nullptr;
	bCanCook = false;
}