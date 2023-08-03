// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Block.h"
#include <Components/BoxComponent.h>

// Sets default values
AEO_Block::AEO_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(50));
	//boxComp->SetCollisionProfileName(TEXT("FoodBox"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	//meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Cube'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(RootComponent);
	sceneComp->SetRelativeLocation(FVector(0, 0, 90));
}

// Called when the game starts or when spawned
void AEO_Block::BeginPlay()
{
	Super::BeginPlay();
	
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
