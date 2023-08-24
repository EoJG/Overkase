// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Stove.h"
#include "EO_Food.h"
#include "EO_Pot.h"
#include <Components/AudioComponent.h>


AEO_Stove::AEO_Stove()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags[0] = TEXT("Stove");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTemp(TEXT("'/Game/01/Interior/Stove.Stove'"));
	if (MeshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(MeshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -45));
	}

	/*ConstructorHelpers::FObjectFinder<USoundBase> TempSizzle(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/BetaSound/PanSizzleStart.PanSizzleStart'"));
	if (TempSizzle.Succeeded())
	{
		sizzleSound = TempSizzle.Object;
	}*/

	ConstructorHelpers::FObjectFinder<USoundBase> TempService(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/BetaSound/ServiceBell.ServiceBell'"));
	if (TempService.Succeeded())
	{
		serviceSound = TempService.Object;
	}

	sizzleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sizzle_AudioComponent"));
	sizzleSound->SetupAttachment(RootComponent); 
	sizzleSound->bAutoActivate = false;
	sizzleSound->SetIsReplicated(true);
}

void AEO_Stove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	//ServerOnIteminTick(DeltaTime);

	if (bCanCook)
	{
		sFoodTemp->curTime += DeltaTime;
		progressWidget->curTime = sFoodTemp->curTime;
		UE_LOG(LogTemp, Warning, TEXT("%f"), sFoodTemp->curTime);
		if (sFoodTemp->curTime >= sFoodTemp->coolTime)
		{
			StopSizzleSound();
			ServerOnServiceSound();
			UE_LOG(LogTemp, Warning, TEXT("IsCoocked"));
			sFoodTemp->bIsCooked = true;
			widgetComp->SetVisibility(false);
		}
		else
		{
			ServerStartSizzleSound();
			widgetComp->SetVisibility(true);
			progressWidget->BindProgressFunc();
		}
	}
	
}

void AEO_Stove::OnItem(class AActor* item)
{
	if (!bOnItem)
	{
		if (AEO_Pot* potItem = Cast<AEO_Pot>(item))
		{
			if (potItem->bInFood)
			{
				TArray<AActor*> items;
				potItem->GetAttachedActors(items);
				sFoodTemp = Cast<AEO_Food>(items[0]);
				progressWidget->coolTime = sFoodTemp->coolTime;

				bCanCook = true;
			}
		}

		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		bOnItem = true;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("OnItem"));
		TArray<AActor*> items;
		GetAttachedActors(items);
		// 테이블 위에 아이템이 접시 일 때
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				return;
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (!plateTemp->bDirty && pPot->bInFood)
				{
					TArray<AActor*> inFoods;
					pPot->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						plateTemp->CheckRecipe(inFoods[0]->Tags[0]);
						pPot->bInFood = false;
					}
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (!plateTemp->bDirty && !plateTemp->CheckOnFood(pFood->Tags[0]) && pFood->bIsCooked)
				{
					item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					if (pFood->bIsOrigin)
						pFood->PlatedVisible();

					plateTemp->CheckRecipe(item->Tags[0]);
				}
			}
		}
		// 테이블 위에 아이템이 냄비 일 때
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && potTemp->bInFood)
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						pPlate->CheckRecipe(inFoods[0]->Tags[0]);
						potTemp->bInFood = false;
					}
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				return;
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (pFood->bCanBoil && !potTemp->bInFood && !pFood->bIsCooked)
				{
					item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

					sFoodTemp = pFood;
					progressWidget->coolTime = sFoodTemp->coolTime;
					potTemp->bInFood = true;
					bCanCook = true;
				}
			}
		}
		// 테이블 위에 아이템이 음식 일 때
		else if (AEO_Food* foodTemp = Cast<AEO_Food>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && !pPlate->CheckOnFood(foodTemp->Tags[0]) && foodTemp->bIsCooked)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					if (foodTemp->bIsOrigin)
						foodTemp->PlatedVisible();

					pPlate->CheckRecipe(foodTemp->Tags[0]);
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (foodTemp->bCanBoil && !pPot->bInFood && !foodTemp->bIsCooked)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToActor(pPot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->meshComp->SetVisibility(false);
					progressWidget->coolTime = sFoodTemp->coolTime;

					pPot->bInFood = true;
					bCanCook = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}

void AEO_Stove::GetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	sFoodTemp = nullptr;
	bCanCook = false;
}


void AEO_Stove::ServerStartSizzleSound_Implementation()
{
	MulticastStartSizzleSound();
}

void AEO_Stove::MulticastStartSizzleSound_Implementation()
{
	sizzleSound->Activate(false);
}

void AEO_Stove::StopSizzleSound()
{
	sizzleSound->Activate(true);
}

void AEO_Stove::ServerOnServiceSound_Implementation()
{
	MulticastOnServiceSound();
}

void AEO_Stove::MulticastOnServiceSound_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Emerald, FString::Printf(TEXT("Service")));
	UGameplayStatics::PlaySound2D(GetWorld(), serviceSound);
}

void AEO_Stove::ServerOnItem2_Implementation(class AActor* item)
{
	MulticastOnItem2(item);
}

void AEO_Stove::MulticastOnItem2_Implementation(class AActor* item)
{
	
	if (!bOnItem)
	{
		if (AEO_Pot* potItem = Cast<AEO_Pot>(item))
		{
			if (potItem->bInFood)
			{
				TArray<AActor*> items;
				potItem->GetAttachedActors(items);
				sFoodTemp = Cast<AEO_Food>(items[0]);
				UE_LOG(LogTemp, Warning, TEXT("sFoodTemp: %s"), sFoodTemp != nullptr ? *FString("Has") : *FString("None"));
				progressWidget->coolTime = sFoodTemp->coolTime;

				bCanCook = true;
			}
		}

		item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		bOnItem = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnItem"));
		TArray<AActor*> items;
		GetAttachedActors(items);
		// 테이블 위에 아이템이 접시 일 때
		if (!items.IsEmpty())
		{
		if (AEO_Plate* plateTemp = Cast<AEO_Plate>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				return;
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (!plateTemp->bDirty && pPot->bInFood)
				{
					TArray<AActor*> inFoods;
					pPot->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						plateTemp->CheckRecipe(inFoods[0]->Tags[0]);
						pPot->bInFood = false;
					}
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (!plateTemp->CheckOnFood(pFood->Tags[0]))
				{
					item->AttachToComponent(plateTemp->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					plateTemp->CheckRecipe(item->Tags[0]);
				}
			}
		}
		// 테이블 위에 아이템이 냄비 일 때
		else if (AEO_Pot* potTemp = Cast<AEO_Pot>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && potTemp->bInFood)
				{
					TArray<AActor*> inFoods;
					potTemp->GetAttachedActors(inFoods);
					if (Cast<AEO_Food>(inFoods[0])->bIsCooked)
					{
						inFoods[0]->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
						Cast<AEO_Food>(inFoods[0])->changeMeshComp->SetVisibility(true);

						pPlate->CheckRecipe(inFoods[0]->Tags[0]);
						potTemp->bInFood = false;
					}
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				return;
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				if (pFood->bCanBoil && !potTemp->bInFood)
				{
					item->AttachToActor(potTemp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					Cast<AEO_Food>(item)->meshComp->SetVisibility(false);

					sFoodTemp = pFood;
					progressWidget->coolTime = sFoodTemp->coolTime;
					potTemp->bInFood = true;
					bCanCook = true;
				}
			}
		}
		// 테이블 위에 아이템이 음식 일 때
		else if (AEO_Food* foodTemp = Cast<AEO_Food>(items[0]))
		{
			if (AEO_Plate* pPlate = Cast<AEO_Plate>(item))
			{
				if (!pPlate->bDirty && !pPlate->CheckOnFood(foodTemp->Tags[0]))
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToComponent(pPlate->sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					pPlate->CheckRecipe(foodTemp->Tags[0]);
				}
			}
			else if (AEO_Pot* pPot = Cast<AEO_Pot>(item))
			{
				if (foodTemp->bCanBoil && !pPot->bInFood)
				{
					item->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->AttachToActor(pPot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
					foodTemp->meshComp->SetVisibility(false);
					progressWidget->coolTime = sFoodTemp->coolTime;

					pPot->bInFood = true;
					bCanCook = true;
				}
			}
			else if (AEO_Food* pFood = Cast<AEO_Food>(item))
			{
				return;
			}
		}
	}
}
	
}

void AEO_Stove::ServerOnIteminTick_Implementation(float DeltaTime)
{
	
}

void AEO_Stove::MulticastOnIteminTick_Implementation(float DeltaTime)
{
	
}

void AEO_Stove::ServerGetItem(class USceneComponent* playerSceneComp)
{
	MulticastGetItem(playerSceneComp);
}

void AEO_Stove::MulticastGetItem(class USceneComponent* playerSceneComp)
{
	Super::GetItem(playerSceneComp);

	sFoodTemp = nullptr;
	bCanCook = false;
}

//void AEO_Stove::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AEO_Stove, sizzleSound);
//}

