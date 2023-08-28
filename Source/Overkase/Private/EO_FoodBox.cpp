// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FoodBox.h"
#include "EO_Food.h"
#include "EO_NonePlate.h"

AEO_FoodBox::AEO_FoodBox()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Tags[0] = TEXT("FoodBox");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/01/Interior/Box_2.Box_2'"));
	if (MeshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(MeshTemp.Object);
	}
}

void AEO_FoodBox::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		bOnItem = false;
	}
	else
	{
		AEO_Food* spawnFood = GetWorld()->SpawnActor<AEO_Food>(food, playerSceneComp->GetComponentTransform());
		spawnFood->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AEO_FoodBox::ServerGetItem(class USceneComponent* playerSceneComp)
{
	MulticastGetItem(playerSceneComp);
}

void AEO_FoodBox::MulticastGetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		if(!items.IsEmpty())
			items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		bOnItem = false;
	}
	else
	{
		AEO_Food* spawnFood = GetWorld()->SpawnActor<AEO_Food>(food, playerSceneComp->GetComponentTransform());
		spawnFood->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}
