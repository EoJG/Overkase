// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Pot.h"

// Sets default values
AEO_Pot::AEO_Pot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Pot"));

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = sceneComp;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Interior/pot.pot'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeRotation(FRotator(0, 90, 0));
		meshComp->SetRelativeScale3D(FVector(1.5f));
	}
	meshComp->SetupAttachment(RootComponent);
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

