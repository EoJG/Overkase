// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseInteraction.h"
#include "EO_Block.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EO_Sink.h"
#include "EO_Plate.h"
#include "EO_Pot.h"
#include "EO_FoodBox.h"


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
}

void UH_OverkaseInteraction::BeginPlay()
{
	Super::BeginPlay();
	// food, block ���͸� �迭�� ����, Ȥ�� ����
	me->interationDistance->OnComponentBeginOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentBeginOverlap);
	me->interationDistance->OnComponentEndOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentEndOverlap);

}

void UH_OverkaseInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// me �� ����� ����� �Ÿ��� ����
	closestBlockIndex = FindClosestBlock();


	if (blockActor.Num() != 0) 
	{
		block = Cast<AEO_Block>(blockActor[closestBlockIndex]);

	}

	// me �� ���� ����� Ǫ���� �Ÿ��� ����
	closestFoodIndex = FindClosestFood();

	if (foodActor.Num() != 0)
	{
		Food = Cast<AEO_Food>(foodActor[closestFoodIndex]);
	}

	if (bIsDoingInteraction)
	{
		block->Interaction();
		UE_LOG(LogTemp,Warning,TEXT("WashingDishes"));
	}
	if (!bPressedCtrl)
	{
		bIsDoingInteraction = false;
	}
	//AEO_Sink* sink = Cast<AEO_Sink>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Sink::StaticClass()));

	
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
	//���ڽ��� ��ǲ ���ε�
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
	// ���� �����̿� �ƹ��͵� ���� ������ 
	if (blockDistance.IsEmpty() && foodDistance.IsEmpty())
	{
		// �ƹ��͵� ���� ����
		return;
	}
	// ���� �������� ���� ��ó�� ����� ������
	if (!bHasItem && !blockDistance.IsEmpty())
	{
		// ����� �����Ͷ�
		ItemOnPlayer();
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// ���� �������� ���� ��ó�� Ǫ�尡 ������
	else if (!bHasItem && !foodDistance.IsEmpty())
	{
		//Ǫ�带 �����Ͷ�
		GetFood(me->interactionPosition);
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// ���� �������� ���� ����� �Ÿ��� Ǫ���� �Ÿ����� ������
	else if (!bHasItem && blockDistance[closestBlockIndex] < foodDistance[closestFoodIndex])
	{
		// ����� �����Ͷ�
		ItemOnPlayer();
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// ���� �������� ���� Ǫ���� �Ÿ��� ����� �Ÿ����� ������
	else if (!bHasItem && blockDistance[closestBlockIndex] > foodDistance[closestFoodIndex])
	{
		//Ǫ�带 �����Ͷ�
		GetFood(me->interactionPosition);
		UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// �������� ������
	else
	{
		// �տ� ����� �������ƶ�
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
		//��� �̱�ó�� ������
		if (blockActor.IsEmpty())
		{
			// �׳ɳѾ��
			return;
		}
		else
		{
			// ����� ���
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

	// ���� �������� �տ� ���������
	if(bHasItem){
		// ���� ��ó�� ����� ���ٸ�
		if (blockActor.IsEmpty())
		{
			// ���� 0���� �ִٸ�
			if (items.IsValidIndex(0))
			{
				// �������� �������ƶ�
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

void UH_OverkaseInteraction::ReleaseFood(class AActor* food)
{
	
}

int32 UH_OverkaseInteraction::FindClosestBlock()
{

	int32 ClosestIndex = 0; // Initialize with an invalid index
	 
	float ShortestDistance = TNumericLimits<float>::Max(); // shortestDistance �� �ִ밪���� ����

	for (int32 i = 0; i < blockActor.Num(); ++i)
	{
		// ����  i��° foodActor �� �Ÿ��� floatDistance �� i��°�� ����
		blockDistance[i] = FVector::Dist(me->GetActorLocation(), blockActor[i]->GetActorLocation());

		float dist = blockDistance[i]; // i��° �Ÿ��� dist �� ����

		//���� dist �� ShortestDistance ���� �۴ٸ�
		if (dist < ShortestDistance)
		{
			ShortestDistance = dist; // ShortestDistance �� Dist�� ����
			ClosestIndex = i; // dist �� ���� ª�ٸ� i �� ���� ����� �ε��� ��ȣ
		}
	}
	return ClosestIndex; // ���� ����� �ε��� ��ȣ�� ����
}


int32 UH_OverkaseInteraction::FindClosestFood()
{

	int32 ClosestIndex = 0; // Initialize with an invalid index
	 
	float ShortestDistance = TNumericLimits<float>::Max(); // shortestDistance �� �ִ밪���� ����

	for (int32 i = 0; i < foodActor.Num(); ++i)
	{
		// ����  i��° foodActor �� �Ÿ��� floatDistance �� i��°�� ����
		foodDistance[i] = FVector::Dist(me->GetActorLocation(), foodActor[i]->GetActorLocation());

		float dist = foodDistance[i]; // i��° �Ÿ��� dist �� ����

		//���� dist �� ShortestDistance ���� �۴ٸ�
		if (dist < ShortestDistance)
		{
			ShortestDistance = dist; // ShortestDistance �� Dist�� ����
			ClosestIndex = i; // dist �� ���� ª�ٸ� i �� ���� ����� �ε��� ��ȣ
		}
	}
	return ClosestIndex; // ���� ����� �ε��� ��ȣ�� ����
}
