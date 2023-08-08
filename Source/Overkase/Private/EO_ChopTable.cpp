// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ChopTable.h"
#include "../Public/EO_Food.h"
#include "EO_NonePlate.h"

AEO_ChopTable::AEO_ChopTable()
{
	PrimaryActorTick.bCanEverTick = true;

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
		}
	}
}
