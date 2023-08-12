// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Block.h"
#include <Components/BoxComponent.h>
#include "EO_Food.h"
#include "EO_NonePlate.h"
#include "EO_Plate.h"
#include "EO_Pot.h"
#include "EO_Plate.h"

// Sets default values
AEO_Block::AEO_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Block"));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(50, 50, 30));
	boxComp->SetCollisionProfileName(TEXT("Block"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocationAndRotation(FVector(0, 0, -30), FRotator(0, -90, 0));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/Box_2_Desk_0.Box_2_Desk_0'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(RootComponent);
	sceneComp->SetRelativeLocation(FVector(0, 0, 50));
	sceneComp->SetRelativeRotation(FRotator(0, -90, 0));

	static ConstructorHelpers::FClassFinder<AEO_Plate> plateTemp(TEXT("/Script/Engine.Blueprint'/Game/Eo/Blueprints/Plate/BP_Plate.BP_Plate_C'"));
	if (plateTemp.Succeeded())
	{
		plate = plateTemp.Class;
	}

	static ConstructorHelpers::FClassFinder<AEO_Pot> potTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Pot.BP_Pot_C'"));
	if (potTemp.Succeeded())
	{
		pot = potTemp.Class;
	}
}

// Called when the game starts or when spawned
void AEO_Block::BeginPlay()
{
	Super::BeginPlay();
	
	if (bSpawnPlate)
	{
		GetWorld()->SpawnActor<AEO_Plate>(plate, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		bOnItem = true;
	}
	else if (bSpawnPot)
	{
		GetWorld()->SpawnActor<AEO_Pot>(pot, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		bOnItem = true;
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
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (!plateTemp->bDirty)
			{
				if (AEO_Pot* potTemp = Cast<AEO_Pot>(item))
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);
					}
				}
				else
				{
					if (!plateTemp->CheckOnFood(Cast<AEO_Food>(item)->Tags[0]))
					{
						item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

						plateTemp->CheckRecipe(item->Tags[0]);
					}
				}
			}
		}
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (Cast<AEO_Food>(item)->bCanBoil && !potTemp->bInFood)
			{
				item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

				potTemp->bInFood = true;
			}
		}
		else if (AEO_Plate* pPlateTemp = Cast<AEO_Plate>(item))
		{
			if (!plateTemp->bDirty)
			{
				if (!pPlateTemp->CheckOnFood(Cast<AEO_Food>(items[0])->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					items[0]->AttachToComponent(pPlateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					pPlateTemp->CheckRecipe(items[0]->Tags[0]);
				}
			}
		}
		else if (AEO_Pot* pPotTemp = Cast<AEO_Pot>(item))
		{
			if (Cast<AEO_Food>(item)->bCanBoil && !pPotTemp->bInFood)
			{
				item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				items[0]->AttachToActor(pPotTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Cast<AEO_Food>(items[0])->meshComp->SetVisibility(false);

				pPotTemp->bInFood = true;
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

