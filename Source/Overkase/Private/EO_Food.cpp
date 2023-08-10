// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Food.h"
#include <Components/BoxComponent.h>

// Sets default values
AEO_Food::AEO_Food()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	boxComp->SetLinearDamping(2.5f);
	boxComp->BodyInstance.bOverrideMass = true;
	boxComp->BodyInstance.SetMassOverride(20);
	boxComp->BodyInstance.bLockRotation = true;
	boxComp->SetCollisionProfileName(TEXT("Food"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Sphere.Sphere'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	changeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeMeshComponent"));
	changeMeshComp->SetupAttachment(RootComponent);
	changeMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	changeMeshComp->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEO_Food::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEO_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEO_Food::ShootFood()
{
	FVector dir = GetAttachParentActor()->GetActorForwardVector() * 30000;

	boxComp->SetSimulatePhysics(true);
	boxComp->AddImpulse(dir);
}

