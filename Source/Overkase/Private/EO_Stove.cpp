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

		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);

		bOnItem = true;
	}
}

void AEO_Stove::GetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	foodTemp = nullptr;
	bCanCook = false;
}