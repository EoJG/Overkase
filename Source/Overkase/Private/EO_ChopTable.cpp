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
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);

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
	if (bOnItem && !food->bIsCooked)
	{
		// 일정 시간이 지난 후 요리를 완성함
		UE_LOG(LogTemp, Warning, TEXT("Maked"));
		food->bIsCooked = true;
	}
}
