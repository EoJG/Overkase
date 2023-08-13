// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseInteraction.h"
#include "H_OverkasePlayerMove.h"
#include "EO_Block.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EO_Sink.h"
#include "EO_Plate.h"
#include "EO_Pot.h"
#include "EO_FoodBox.h"
#include "EO_ChopTable.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

UH_OverkaseInteraction::UH_OverkaseInteraction()
{
	ConstructorHelpers::FObjectFinder<UInputAction> TempSpace(TEXT("/Script/EnhancedInput.InputAction'/Game/HanSeunghui/Input/IA_OverKaseSpace.IA_OverKaseSpace'"));
	if (TempSpace.Succeeded())
	{
		ia_Space_Interaction = TempSpace.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> TempCtrl(TEXT("/Script/EnhancedInput.InputAction'/Game/HanSeunghui/Input/IA_OverkaseCtrl.IA_OverkaseCtrl'"));
	if (TempCtrl.Succeeded())
	{
		ia_ctrl_Interaction = TempCtrl.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> TempPick(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Item_PickUp_02.Item_PickUp_02'"));
	if (TempPick.Succeeded())
	{
		pickUpSound = TempPick.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> TempPut(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Item_PutDown_01.Item_PutDown_01'"));
	if (TempPut.Succeeded())
	{
		putDownSound = TempPut.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempThrow(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Throw1.Throw1'"));
	if (TempThrow.Succeeded())
	{
		throwSound = TempThrow.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempChop(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/KnifeChop.KnifeChop'"));
	if (TempChop.Succeeded())
	{
		chopSound = TempChop.Object;
	}
}

void UH_OverkaseInteraction::BeginPlay()
{
	Super::BeginPlay();
	// food, block 액터를 배열에 저장, 혹은 제거
	me->interationDistance->OnComponentBeginOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentBeginOverlap);
	me->interationDistance->OnComponentEndOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentEndOverlap);

}

void UH_OverkaseInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	space = Cast<UH_OverkasePlayerMove>(me->overPlayerMove);
	
	// me 와 가까운 블록의 거리를 저장
	closestBlockIndex = FindClosestBlock();


	if (blockActor.Num() != 0) 
	{
		block = Cast<AEO_Block>(blockActor[closestBlockIndex]);

	}

	// me 와 가장 가까운 푸드의 거리를 저장
	closestFoodIndex = FindClosestFood();

	if (foodActor.Num() != 0)
	{
		Food = Cast<AEO_Food>(foodActor[closestFoodIndex]);
	}

	if (!bPressedCtrl)
	{
		bIsDoingInteraction = false;
	}
	if (blockActor.IsEmpty() == false) {
		if (bIsDoingInteraction)
		{
			block->Interaction();

			if (blockActor[closestBlockIndex]->GetName().Contains(FString("Sink")))
			{
				
				//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Emerald, FString::Printf(TEXT("%s"), *blockActor[closestBlockIndex]->GetName()));
				if (!bIsInteraction) {
					WashHand();
				}
				
			}
			else if (blockActor[closestBlockIndex]->GetName().Contains(FString("ChopTable")))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Cyan, FString::Printf(TEXT("%s"), *blockActor[closestBlockIndex]->GetName()));
				if (!bIsInteraction) {
					ChopHand();
				}
				if (!bSoundPlay) {
					SoundPlay();
				}
			}

		}
		else if (!bIsDoingInteraction && blockActor[closestBlockIndex]->GetName().Contains(FString("Sink")))
		{
			me->AnimationComponent->CallWashHand(false);
			me->AnimationComponent->DownHand();
			bIsInteraction = false;
		}
		else if (!bIsDoingInteraction && blockActor[closestBlockIndex]->GetName().Contains(FString("ChopTable")))
		{
			me->AnimationComponent->CallChopHand(false);
			me->AnimationComponent->DownHand();
			bIsInteraction = false;


		}
	}

	
	
	me->GetAttachedActors(items);

	if (items.IsEmpty())
	{
		bHasItem = false;
	}
	else
	{
		bHasItem = true;
	}
	
}

void UH_OverkaseInteraction::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{	
	//인핸스드 인풋 바인딩
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (pInput) 
	{
		pInput->BindAction(ia_Space_Interaction, ETriggerEvent::Triggered, this, &UH_OverkaseInteraction::SpaceInput);
		pInput->BindAction(ia_ctrl_Interaction, ETriggerEvent::Started, this, &UH_OverkaseInteraction::CtrlInput);
		pInput->BindAction(ia_ctrl_Interaction, ETriggerEvent::Completed, this, &UH_OverkaseInteraction::CtrlCompleted);

	}
	
}

void UH_OverkaseInteraction::SpaceInput()
{	
	// 만약 가까이에 아무것도 있지 않으면 
	if (blockDistance.IsEmpty() && foodDistance.IsEmpty())
	{
		// 아무것도 하지 마라
		return;
	}
	// 만약 아이템이 없고 근처에 블록이 있으면
	if (!bHasItem && !blockDistance.IsEmpty())
	{
		// 블록을 가져와라
		ItemOnPlayer();
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// 만약 아이템이 없고 근처에 푸드가 있으면
	else if (!bHasItem && !foodDistance.IsEmpty())
	{
		//푸드를 가져와라
		GetFood(me->interactionPosition);
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// 만약 아이템이 없고 블록의 거리가 푸드의 거리보다 가까우면
	else if (!bHasItem && blockDistance[closestBlockIndex] < foodDistance[closestFoodIndex])
	{
		// 블록을 가져와라
		ItemOnPlayer();
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// 만약 아이템이 없고 푸드의 거리가 블록의 거리보다 가까우면
	else if (!bHasItem && blockDistance[closestBlockIndex] > foodDistance[closestFoodIndex])
	{
		//푸드를 가져와라
		GetFood(me->interactionPosition);
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// 아이템이 없으면
	else
	{
		// 손에 든것을 내려놓아라
		NoItem();
		UGameplayStatics::PlaySound2D(GetWorld(), putDownSound);

	}
}

void UH_OverkaseInteraction::CtrlInput()
{
	bPressedCtrl = true;
	
	if(bHasItem)
	{
		AEO_Food* food = Cast<AEO_Food>(items[0]);
		if (!items.IsEmpty()) {
			if (items[0] == food)
			{
				items[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				Food->ShootFood(me->GetActorForwardVector());
				UGameplayStatics::PlaySound2D(GetWorld(), throwSound);

			}
		}
	}
	else if (block != nullptr &&  block->bIsInterObj)
	{
		bIsDoingInteraction = true;
	}
}

void UH_OverkaseInteraction::ItemOnPlayer()
{
	if(!bHasItem)
	{
		//블록 이근처에 없으면
		if (blockActor.IsEmpty())
		{
			// 그냥넘어가라
			return;
		}
		else
		{
			// 블록을 든다
			if (block) 
			{
				block->GetItem(me->interactionPosition);

				if (items.IsEmpty() == false) 
				{
					//bHasItem = true;
				}
			}
		}
	}
}

void UH_OverkaseInteraction::NoItem()
{
	//AEO_Plate* plate = Cast<AEO_Plate>(items[0]);
	//AEO_Pot* pot = Cast<AEO_Pot>(items[0]);

	// 만약 아이템을 손에 들고있으면
	if(bHasItem){
		// 만약 근처에 블록이 없다면
		if (blockActor.IsEmpty())
		{
			// 만약 0번이 있다면
			if (items.IsValidIndex(0))
			{
				// 아이템을 내려놓아라
				Food->boxComp->SetSimulatePhysics(true);
				items[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			}
			//bHasItem = false;
		}
		else
		{
			if (!items.IsEmpty()) 
			{
				block->OnItem(items[0]);
				if (items.IsEmpty()) 
				{
					//bHasItem = false;
				}
			}
		}
	}
}

void UH_OverkaseInteraction::CtrlCompleted()
{
	bPressedCtrl = false;
}

void UH_OverkaseInteraction::SoundPlay()
{
	bSoundPlay = true;

	UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(this, chopSound);
	FTimerHandle soundTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	// 3초 후에 사운드 중지
	TimerManager.SetTimer(soundTimerHandle, [this, AudioComp]()
		{
			AudioComp->Stop();
			bSoundPlay = false;
		}, 0.2f, false);
}

void UH_OverkaseInteraction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEO_Block* temp = Cast<AEO_Block>(OtherActor))
	{
		blockActor.Add(temp);
		blockDistance.Add(0);
	}

	if (AEO_Food* food = Cast<AEO_Food>(OtherActor))
	{
		foodActor.Add(food);
		foodDistance.Add(0);
	}
}

void UH_OverkaseInteraction::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEO_Block* temp = Cast<AEO_Block>(OtherActor))
	{
		blockActor.Remove(temp);
		blockDistance.RemoveAt(0);
	}

	if (AEO_Food* food = Cast<AEO_Food>(OtherActor))
	{
		UE_LOG(LogTemp,Warning, TEXT("GetFood"));
		foodActor.Remove(food);
		foodDistance.RemoveAt(0);
	}
}

void UH_OverkaseInteraction::GetFood(class USceneComponent* playerSceneComp)
{
	Food = Cast<AEO_Food>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Food::StaticClass()));
	if (Food)
	{
		if (!bHasItem)
		{
			if (foodActor.IsEmpty()) {
				return;
			}
			foodActor[closestFoodIndex]->boxComp->SetSimulatePhysics(false);
			foodActor[closestFoodIndex]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			bHasItem = true;
		}
	}
}


void UH_OverkaseInteraction::WashHand()
{
	bIsInteraction = true;
	me->AnimationComponent->CallWashHand(true);
}

void UH_OverkaseInteraction::ChopHand()
{
	bIsInteraction = true;
	me->AnimationComponent->CallChopHand(true);
}

int32 UH_OverkaseInteraction::FindClosestBlock()
{

	int32 ClosestIndex = 0; // Initialize with an invalid index
	 
	float ShortestDistance = TNumericLimits<float>::Max(); // shortestDistance 를 최대값으로 만듦

	for (int32 i = 0; i < blockActor.Num(); ++i)
	{
		// 나와  i번째 foodActor 의 거리를 floatDistance 의 i번째에 저장
		blockDistance[i] = FVector::Dist(me->GetActorLocation(), blockActor[i]->GetActorLocation());

		float dist = blockDistance[i]; // i번째 거리를 dist 에 저장

		//만약 dist 가 ShortestDistance 보다 작다면
		if (dist < ShortestDistance)
		{
			ShortestDistance = dist; // ShortestDistance 는 Dist로 저장
			ClosestIndex = i; // dist 가 제일 짧다면 i 는 제일 가까운 인덱스 번호
		}
	}
	return ClosestIndex; // 제일 가까운 인덱스 번호를 저장
}


int32 UH_OverkaseInteraction::FindClosestFood()
{

	int32 ClosestIndex = 0; // Initialize with an invalid index
	 
	float ShortestDistance = TNumericLimits<float>::Max(); // shortestDistance 를 최대값으로 만듦

	for (int32 i = 0; i < foodActor.Num(); ++i)
	{
		// 나와  i번째 foodActor 의 거리를 floatDistance 의 i번째에 저장
		foodDistance[i] = FVector::Dist(me->GetActorLocation(), foodActor[i]->GetActorLocation());

		float dist = foodDistance[i]; // i번째 거리를 dist 에 저장

		//만약 dist 가 ShortestDistance 보다 작다면
		if (dist < ShortestDistance)
		{
			ShortestDistance = dist; // ShortestDistance 는 Dist로 저장
			ClosestIndex = i; // dist 가 제일 짧다면 i 는 제일 가까운 인덱스 번호
		}
	}
	return ClosestIndex; // 제일 가까운 인덱스 번호를 저장
}
