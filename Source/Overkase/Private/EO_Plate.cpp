// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Plate.h"
#include "Components/SceneComponent.h"

// Sets default values
AEO_Plate::AEO_Plate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Plate"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/00/Interior/plate.plate'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}
	changeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeMeshComponent"));
	changeMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	changeMeshComp->SetupAttachment(meshComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cMeshTemp(TEXT("'/Game/00/Interior/plate_2.plate_2'"));
	if (cMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(cMeshTemp.Object);
	}
	changeMeshComp->SetVisibility(false);

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(meshComp);
	sceneComp->SetRelativeLocation(FVector(0, 0, 25));

	ConstructorHelpers::FClassFinder<AEO_Food> cSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_CucumberSushi.BP_CucumberSushi_C'");
	if (cSushiTemp.Succeeded())
	{
		cucumberSushi = cSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> fSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_FishSushi.BP_FishSushi_C'");
	if (fSushiTemp.Succeeded())
	{
		fishSushi = fSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> oSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_OctopusSushi.BP_OctopusSushi_C'");
	if (oSushiTemp.Succeeded())
	{
		octopusSushi = oSushiTemp.Class;
	}

	ConstructorHelpers::FClassFinder<AEO_Food> rcTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_RiceAndCucumber.BP_RiceAndCucumber_C'");
	if (rcTemp.Succeeded())
	{
		riceCucumber = rcTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> rfTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_RiceAndFish.BP_RiceAndFish_C'");
	if (rfTemp.Succeeded())
	{
		riceFish = rfTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> scTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_SeaweedAndCucumber.BP_SeaweedAndCucumber_C'");
	if (scTemp.Succeeded())
	{
		seaweedCucumber = scTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> sfTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_SeaweedAndFish.BP_SeaweedAndFish_C'");
	if (sfTemp.Succeeded())
	{
		seaweedFish = sfTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_Food> srTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_SeaweedAndRice.BP_SeaweedAndRice_C'");
	if (srTemp.Succeeded())
	{
		seaweedRice = srTemp.Class;
	}

	bReplicates = true;
	meshComp->SetIsReplicated(true);
	changeMeshComp->SetIsReplicated(true);
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
	
	if (!bIsComplete)
	{
		MakeCompleteFood();
	}

	if (!bDirty)
	{
		meshComp->SetVisibility(true);
		changeMeshComp->SetVisibility(false);
	}
	else
	{
		meshComp->SetVisibility(false);
		changeMeshComp->SetVisibility(true);
	}
}

void AEO_Plate::MakeCompleteFood()
{
	if (bIsRice && bIsSeaweed)
	{
		TArray<AActor*> foods;
		GetAttachedActors(foods);
		if (bIsCucumber)
		{
			ReplateFood(foods, cucumberSushi);

			bIsComplete = true;
		}
		else if (bIsFish)
		{
			ReplateFood(foods, fishSushi);

			bIsComplete = true;
		}
		else if (bIsOctopus)
		{
			ReplateFood(foods, octopusSushi);

			bIsComplete = true;
		}
		else
		{
			ReplateFood(foods, seaweedRice);
		}
	}
	else if (bIsRice)
	{
		TArray<AActor*> foods;
		GetAttachedActors(foods);
		if (bIsCucumber)
		{
			ReplateFood(foods, riceCucumber);
		}
		else if (bIsFish)
		{
			ReplateFood(foods, riceFish);
		}
		else if (bIsOctopus)
		{
			for (AActor* food : foods)
			{
				food->Destroy();
			}
		}
	}
	else if (bIsSeaweed)
	{
		TArray<AActor*> foods;
		GetAttachedActors(foods);
		if (bIsCucumber)
		{
			ReplateFood(foods, seaweedCucumber);
		}
		else if (bIsFish)
		{
			ReplateFood(foods, seaweedFish);
		}
		else if (bIsOctopus)
		{
			for (AActor* food : foods)
			{
				food->Destroy();
			}
		}
	}
}

void AEO_Plate::CheckRecipe(FName foodTag)
{
	if (foodTag == TEXT("Rice"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is rice"));
		bIsRice = true;
	}
	else if (foodTag == TEXT("Seaweed"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is seaweed"));
		bIsSeaweed = true;
	}
	else if (foodTag == TEXT("Cucumber"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is cucumber"));
		bIsCucumber = true;
	}
	else if (foodTag == TEXT("Fish"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is fish"));
		bIsFish = true;
	}
	else if (foodTag == TEXT("Octopus"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Octopus"));
		bIsOctopus = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO have recipe"));
	}
}

bool AEO_Plate::CheckOnFood(FName foodTag)
{
	if (foodTag == TEXT("Rice"))
	{
		return bIsRice;
	}
	else if (foodTag == TEXT("Seaweed"))
	{
		return bIsSeaweed;
	}
	else if (foodTag == TEXT("Cucumber"))
	{
		return bIsCucumber;
	}
	else if (foodTag == TEXT("Fish"))
	{
		return bIsFish;
	}
	else if (foodTag == TEXT("Octopus"))
	{
		return bIsOctopus;
	}

	return false;
}

void AEO_Plate::ReplateFood(TArray<AActor*> foods, TSubclassOf<class AEO_Food> spawnFood)
{
	for (AActor* food : foods)
	{
		food->Destroy();
	}
	GetWorld()->SpawnActor<AEO_Food>(spawnFood, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

