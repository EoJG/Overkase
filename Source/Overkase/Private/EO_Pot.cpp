// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Pot.h"

// Sets default values
AEO_Pot::AEO_Pot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/Pot.Pot'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}
}

// Called when the game starts or when spawned
void AEO_Pot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEO_Pot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

