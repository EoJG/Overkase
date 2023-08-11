// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_OrderTable.h"
#include <Kismet/GameplayStatics.h>

AEO_OrderTable::AEO_OrderTable()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("OrderTable");

	boxComp->SetBoxExtent(FVector(75, 150, 45));

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Interior/S_Servingrail.S_Servingrail'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	ConstructorHelpers::FClassFinder<AEO_ReturnPlate> rpTemp(TEXT("'/Game/Eo/Blueprints/Object/BP_ReturnPlate.BP_ReturnPlate_C'"));
	if (rpTemp.Succeeded())
	{
		returnPlate = rpTemp.Class;
	}
}

void AEO_OrderTable::BeginPlay()
{
	Super::BeginPlay();

	wReturnPlate = Cast<AEO_ReturnPlate>(UGameplayStatics::GetActorOfClass(GetWorld(), returnPlate));
}

void AEO_OrderTable::OnItem(class AActor* item)
{
	if (AEO_Plate* plateTemp = Cast<AEO_Plate>(item))
	{
		if (!bOnItem && plateTemp->bIsComplete)
		{
			item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			
			TArray<AActor*> items;
			item->GetAttachedActors(items);
			items[0]->Destroy();
			item->Destroy();

			wReturnPlate->SpawnPlate();
		}
	}
}
