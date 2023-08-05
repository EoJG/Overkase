// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Plate.h"
#include "Components/SceneComponent.h"

// Sets default values
AEO_Plate::AEO_Plate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/plate.plate'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(meshComp);
}

// Called when the game starts or when spawned
void AEO_Plate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEO_Plate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

