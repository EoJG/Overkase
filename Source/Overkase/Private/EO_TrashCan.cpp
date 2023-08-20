// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_TrashCan.h"

AEO_TrashCan::AEO_TrashCan()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("TrashCan");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/01/Interior/trash.trash'"));
	if (MeshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(MeshTemp.Object);
	}
}

void AEO_TrashCan::OnItem(class AActor* item)
{
	if (!bOnItem)
	{
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		item->Destroy();
	}
}

void AEO_TrashCan::ServerOnItem(class AActor* item)
{
	MulticastOnItem(item);
}

void AEO_TrashCan::MulticastOnItem(class AActor* item)
{
	if (!bOnItem)
	{
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		item->Destroy();
	}
}
