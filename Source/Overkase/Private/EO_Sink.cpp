// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Sink.h"

AEO_Sink::AEO_Sink()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("Sink");

	boxComp->SetBoxExtent(FVector(50, 100, 30));

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/01/Interior/sink.sink'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeRotation(FRotator(0, 0, 0));
	}

	sceneComp->SetRelativeLocation(FVector(0, -80, 50));

	ConstructorHelpers::FClassFinder<AEO_Plate> pTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Plates.BP_Plates_C'"));
	if (pTemp.Succeeded())
	{
		plate = pTemp.Class;
	}
}

void AEO_Sink::BeginPlay()
{
	Super::BeginPlay();

	bIsInterObj = true;
}

void AEO_Sink::OnItem(class AActor* item)
{
	if (AEO_Plate* plateTemp = Cast<AEO_Plate>(item))
	{
		if (plateTemp->bDirty)
		{
			item->Destroy();
			progressWidget->coolTime = coolTime;
			plateCount++;
		}
	}
}

void AEO_Sink::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		compleCount--;

		if (compleCount <= 0)
			bOnItem = false;
	}
}

void AEO_Sink::Interaction()
{
	if (plateCount > 0)
	{
		curTime += GetWorld()->DeltaTimeSeconds;
		progressWidget->curTime = curTime;
		if (curTime >= coolTime)
		{
			ServerSpawnPlate();
			widgetComp->SetVisibility(false);
			plateCount--;
			curTime = 0;
		}
		else
		{
			widgetComp->SetVisibility(true);
			progressWidget->BindProgressFunc();
		}
	}
}

void AEO_Sink::SpawnPlate()
{
	GetWorld()->SpawnActor<AEO_Plate>(plate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	compleCount++;

	bOnItem = true;
}

void AEO_Sink::ServerOnItem(class AActor* item)
{
	MulticastOnItem(item);
}

void AEO_Sink::MulticastOnItem(class AActor* item)
{
	if (AEO_Plate* plateTemp = Cast<AEO_Plate>(item))
	{
		if (plateTemp->bDirty)
		{
			item->Destroy();
			progressWidget->coolTime = coolTime;
			plateCount++;
		}
	}
}

void AEO_Sink::ServerGetItem(class USceneComponent* playerSceneComp)
{
	MulticastGetItem(playerSceneComp);
}

void AEO_Sink::MulticastGetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		compleCount--;

		if (compleCount <= 0)
			bOnItem = false;
	}
}

void AEO_Sink::ServerInteraction()
{
	MulticastInteraction();
}

void AEO_Sink::MulticastInteraction()
{
	if (plateCount > 0)
	{
		curTime += GetWorld()->DeltaTimeSeconds;
		progressWidget->curTime = curTime;
		if (curTime >= coolTime)
		{
			ServerSpawnPlate();
			widgetComp->SetVisibility(false);
			plateCount--;
			curTime = 0;
		}
		else
		{
			widgetComp->SetVisibility(true);
			progressWidget->BindProgressFunc();
		}
	}
}

void AEO_Sink::ServerSpawnPlate_Implementation()
{
	GetWorld()->SpawnActor<AEO_Plate>(plate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	compleCount++;

	bOnItem = true;
}
