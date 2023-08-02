// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_FoodBox.h"
#include "EO_Food.h"

AEO_FoodBox::AEO_FoodBox()
{
	PrimaryActorTick.bCanEverTick = true;

	/*meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}*/
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
		AEO_Food* spawnFood = GetWorld()->SpawnActor<AEO_Food>(food, playerSceneComp->GetComponentTransform());
		spawnFood->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}
