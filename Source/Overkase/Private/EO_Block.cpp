// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Block.h"
#include <Components/BoxComponent.h>
#include "EO_Food.h"
#include "EO_NonePlate.h"
#include "EO_Plate.h"
#include "EO_Pot.h"
#include "EO_Plate.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "EO_Progressbar.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEO_Block::AEO_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Block"));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(75, 75, 45));
	boxComp->SetCollisionProfileName(TEXT("Block"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocationAndRotation(FVector(0, 0, -45), FRotator(0, -90, 0));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Interior/Desk.Desk'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(RootComponent);
	sceneComp->SetRelativeLocation(FVector(0, 0, 50));
	sceneComp->SetRelativeRotation(FRotator(0));

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	widgetComp->SetupAttachment(RootComponent);
	widgetComp->SetRelativeLocation(FVector(-80, 0, 0));
	static ConstructorHelpers::FClassFinder<UUserWidget> progressTemp(TEXT("'/Game/Eo/Blueprints/UI/BP_UI_Progressbar.BP_UI_Progressbar_C'"));
	if (progressTemp.Succeeded())
	{
		widgetComp->SetWidgetClass(progressTemp.Class);
	}
	widgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<AEO_Plate> plateTemp(TEXT("/Script/Engine.Blueprint'/Game/Eo/Blueprints/Plate/BP_Plates.BP_Plates_C'"));
	if (plateTemp.Succeeded())
	{
		plate = plateTemp.Class;
	}

	static ConstructorHelpers::FClassFinder<AEO_Pot> potTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Pot.BP_Pot_C'"));
	if (potTemp.Succeeded())
	{
		pot = potTemp.Class;
	}

	bReplicates = true;
}

// Called when the game starts or when spawned
void AEO_Block::BeginPlay()
{
	Super::BeginPlay();

	widgetComp->SetWorldLocation(GetActorLocation() + FVector(-80, 0, 0));
	widgetComp->SetVisibility(false);
	progressWidget = Cast<UEO_Progressbar>(widgetComp->GetUserWidgetObject());
	
	if (bSpawnPlate)
	{
		
		ServerOnSpawnPlate();
	}
	else if (bSpawnPot)
	{
		ServerPutSpawnPlate();
	}
}

// Called every frame
void AEO_Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEO_Block::OnItem(class AActor* item)
{
	if (!bOnItem)
	{
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		bOnItem = true;
	}
	else
	{
		TArray<AActor*> items;
		GetAttachedActors(items);
		// 테이블 위에 아이템이 접시 일 때
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				return;
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (!plateTemp->bDirty && pPot->bInFood)
				{
					TArray<AActor*> inFoods;
					pPot->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						plateTemp->CheckRecipe(inFoods[0]->Tags[0]);
						pPot->bInFood = false;
					}
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (!plateTemp->CheckOnFood(pFood->Tags[0]))
				{
					item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					plateTemp->CheckRecipe(item->Tags[0]);
				}
			}
		}
		// 테이블 위에 아이템이 냄비 일 때
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (AEO_Plate * pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && potTemp->bInFood)
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						pPlate->CheckRecipe(inFoods[0]->Tags[0]);
						potTemp->bInFood = false;
					}
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				return;
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (pFood->bCanBoil && !potTemp->bInFood)
				{
					item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

					potTemp->bInFood = true;
				}
			}
		}
		// 테이블 위에 아이템이 음식 일 때
		else if (AEO_Food* foodTemp = Cast<AEO_Food>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && !pPlate->CheckOnFood(foodTemp->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					pPlate->CheckRecipe(foodTemp->Tags[0]);
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (foodTemp->bCanBoil && !pPot->bInFood)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToActor(pPot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->meshComp->SetVisibility(false);

					pPot->bInFood = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}

void AEO_Block::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		bOnItem = false;
	}
}

void AEO_Block::Interaction()
{
	
}

void AEO_Block::ServerOnItem_Implementation(class AActor* item)
{
	MulticastOnItem(item);
}

void AEO_Block::MulticastOnItem_Implementation(class AActor* item)
{
	if (!bOnItem)
	{
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		bOnItem = true;
	}
	else
	{
		TArray<AActor*> items;
		GetAttachedActors(items);
		// 테이블 위에 아이템이 접시 일 때
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				return;
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (!plateTemp->bDirty && pPot->bInFood)
				{
					TArray<AActor*> inFoods;
					pPot->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						plateTemp->CheckRecipe(inFoods[0]->Tags[0]);
						pPot->bInFood = false;
					}
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (!plateTemp->bDirty && !plateTemp->CheckOnFood(pFood->Tags[0]))
				{
					item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					if(pFood->bIsOrigin)
						pFood->PlatedVisible();

					plateTemp->CheckRecipe(item->Tags[0]);
				}
			}
		}
		// 테이블 위에 아이템이 냄비 일 때
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && potTemp->bInFood)
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						pPlate->CheckRecipe(inFoods[0]->Tags[0]);
						potTemp->bInFood = false;
					}
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				return;
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (pFood->bCanBoil && !potTemp->bInFood)
				{
					item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

					potTemp->bInFood = true;
				}
			}
		}
		// 테이블 위에 아이템이 음식 일 때
		else if (AEO_Food* foodTemp = Cast<AEO_Food>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && !pPlate->CheckOnFood(foodTemp->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					if (foodTemp->bIsOrigin)
						foodTemp->PlatedVisible();

					pPlate->CheckRecipe(foodTemp->Tags[0]);
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (foodTemp->bCanBoil && !pPot->bInFood)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToActor(pPot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->meshComp->SetVisibility(false);

					pPot->bInFood = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}

void AEO_Block::ServerGetItem_Implementation(class USceneComponent* playerSceneComp)
{
	MulticastGetItem(playerSceneComp);
}

void AEO_Block::MulticastGetItem_Implementation(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		bOnItem = false;
	}
}

void AEO_Block::ServerInteraction_Implementation()
{
	
}

void AEO_Block::MulticastInteraction_Implementation()
{
	
}

void AEO_Block::ServerOnSpawnPlate_Implementation()
{
	GetWorld()->SpawnActor<AEO_Plate>(plate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	bOnItem = true;
}

void AEO_Block::ServerPutSpawnPlate_Implementation()
{
	GetWorld()->SpawnActor<AEO_Pot>(pot, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	bOnItem = true;
}



//void AEO_Block::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	/*DOREPLIFETIME(AEO_Block, bOnItem);*/
//}
