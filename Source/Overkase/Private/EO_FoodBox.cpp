// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FoodBox.h"
#include "EO_Food.h"
#include "EO_NonePlate.h"

AEO_FoodBox::AEO_FoodBox()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Engine/BasicShapes/Cylinder'"));
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

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
		bOnItem = false;
	}
	else
	{
		AEO_NonePlate* noneP = GetWorld()->SpawnActor<AEO_NonePlate>(nonePlate, playerSceneComp->GetComponentTransform());
		AEO_Food* spawnFood = GetWorld()->SpawnActor<AEO_Food>(food, playerSceneComp->GetComponentTransform());
		spawnFood->AttachToActor(noneP, FAttachmentTransformRules::SnapToTargetIncludingScale);
		noneP->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}
