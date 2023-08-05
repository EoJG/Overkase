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
	}
	else
	{
		TArray<AActor*> items;
		GetAttachedActors(items);
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]) /*AEO_Plate* plateTemp = Cast<AEO_Plate>(item)*/)
		{
			UE_LOG(LogTemp, Warning, TEXT("in"));
			TArray<AActor*> foods;

			item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			GetAttachedActors(foods);
			foods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}

	bOnItem = true;
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

