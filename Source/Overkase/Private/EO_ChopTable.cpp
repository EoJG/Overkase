// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ChopTable.h"
#include "../Public/EO_Food.h"

AEO_ChopTable::AEO_ChopTable()
{
	PrimaryActorTick.bCanEverTick = true;


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
		}

		bOnItem = true;
	}
}

void AEO_ChopTable::Chop()
{
	if (bOnItem && !food->bIsCooked)
	{
		// ���� �ð��� ���� �� �丮�� �ϼ���
		food->bIsCooked = true;
	}
}
