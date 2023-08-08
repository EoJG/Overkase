// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FoodBox.h"
#include "EO_Food.h"
#include "EO_NonePlate.h"

AEO_FoodBox::AEO_FoodBox()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/Models/Probs/Box_Box.Box_Box'"));
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
