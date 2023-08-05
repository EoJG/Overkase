// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Block.h"
#include <Components/BoxComponent.h>
#include "EO_Food.h"
#include "EO_NonePlate.h"
#include "EO_Pot.h"

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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/Box_2_Desk_0.Box_2_Desk_0'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(RootComponent);
	sceneComp->SetRelativeLocation(FVector(0, 0, 50));

	ConstructorHelpers::FClassFinder<AEO_Pot> potTemp(TEXT("'/Game/Eo/Blueprints/Plate/BP_Pot.BP_Pot_C'"));
	if (potTemp.Succeeded())
	{
		pot = potTemp.Class;
	}
	
}

// Called when the game starts or when spawned
void AEO_Block::BeginPlay()
{
	Super::BeginPlay();
	
	if (bSpawnPot)
	{
		GetWorld()->SpawnActor<AEO_Pot>(pot, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
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
		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
		bOnItem = true;
	}
}

void AEO_Block::GetItem(class USceneComponent* playerSceneComp)
{
	if (bOnItem)
	{
		TArray<AActor*> items;
		GetAttachedActors(items);

		items[0]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
		bOnItem = false;
	}
}

void AEO_Block::Interaction()
{

}

