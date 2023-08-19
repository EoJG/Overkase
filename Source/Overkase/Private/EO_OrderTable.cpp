// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_OrderTable.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>

AEO_OrderTable::AEO_OrderTable()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("OrderTable");

	boxComp->SetBoxExtent(FVector(75, 150, 45));

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Interior/Servingrail.Servingrail'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeRotation(FRotator(0, 0, 0));
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

void AEO_OrderTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			menuInter->SubmitMenu(items[0]->Tags[0]);

			items[0]->Destroy();
			item->Destroy();

			wReturnPlate->SpawnPlate();
		}
	}
}

void AEO_OrderTable::ServerOnItem(class AActor* item)
{
	MulticastOnItem(item);
}

void AEO_OrderTable::MulticastOnItem(class AActor* item)
{
	if (AEO_Plate* plateTemp = Cast<AEO_Plate>(item))
	{
		if (!bOnItem && plateTemp->bIsComplete)
		{
			item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			TArray<AActor*> items;
			item->GetAttachedActors(items);
			Cast<AH_OverkaseCharacter>(GetOwner())->inGameUI->ServerSubmitMenu(items[0]->Tags[0]);

			items[0]->Destroy();
			item->Destroy();

			wReturnPlate->SpawnPlate();
		}
	}
}
