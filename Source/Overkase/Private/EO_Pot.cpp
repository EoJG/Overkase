// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Pot.h"
#include "Net/UnrealNetwork.h"

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

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComp->SetupAttachment(meshComp);
	boxComp->SetBoxExtent(FVector(36));
	boxComp->SetRelativeLocation(FVector(0, 0,33));
	boxComp->SetCollisionProfileName(TEXT("Plate"));

	waterMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaterMeshComponent"));
	waterMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> waterMeshTemp(TEXT("'/Game/01/Interior/Pot_W.Pot_W'"));
	if (waterMeshTemp.Succeeded())
	{
		waterMeshComp->SetStaticMesh(waterMeshTemp.Object);
		waterMeshComp->SetRelativeLocation(FVector(0, 0, 90));
		waterMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
		waterMeshComp->SetRelativeScale3D(FVector(1.5f));
	}
	waterMeshComp->SetupAttachment(RootComponent);

	bReplicates = true;
	meshComp->SetIsReplicated(true);
	waterMeshComp->SetIsReplicated(true);
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

	waterMeshComp->SetVisibility(bInFood);
}

void AEO_Pot::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	//DOREPLIFETIME(AEO_Pot, bInFood);
	DOREPLIFETIME(AEO_Pot, bInFood);

}

