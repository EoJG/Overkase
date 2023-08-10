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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/02/plate.plate'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComp->SetupAttachment(meshComp);

	ConstructorHelpers::FClassFinder<AEO_CucumberSushi> cSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_CucumberSushi.BP_CucumberSushi_C'");
	if (cSushiTemp.Succeeded())
	{
		cucumberSushi = cSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_FishSushi> fSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_FishSushi.BP_FishSushi_C'");
	if (fSushiTemp.Succeeded())
	{
		fishSushi = fSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_OctopusSushi> oSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_OctopusSushi.BP_OctopusSushi_C'");
	if (oSushiTemp.Succeeded())
	{
		octopusSushi = oSushiTemp.Class;
	}
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
}

void AEO_Plate::MakeCompleteFood()
{
	if (bIsRice && bIsSeaweed)
	{
		if (bIsCucumber)
		{
			TArray<AActor*> foods;
			GetAttachedActors(foods);
			for (AActor* food : foods)
			{
				food->Destroy();
			}
			GetWorld()->SpawnActor<AEO_CucumberSushi>(cucumberSushi, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			bIsComplete = true;
		}
		else if (bIsFish)
		{
			TArray<AActor*> foods;
			GetAttachedActors(foods);
			for (AActor* food : foods)
			{
				food->Destroy();
			}
			GetWorld()->SpawnActor<AEO_FishSushi>(fishSushi, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			bIsComplete = true;
		}
		else if (bIsOctopus)
		{
			TArray<AActor*> foods;
			GetAttachedActors(foods);
			for (AActor* food : foods)
			{
				food->Destroy();
			}
			GetWorld()->SpawnActor<AEO_OctopusSushi>(octopusSushi, sceneComp->GetComponentLocation(), sceneComp->GetComponentRotation())->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			bIsComplete = true;
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

