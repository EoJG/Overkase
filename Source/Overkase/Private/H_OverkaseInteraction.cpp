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
#include "Net/UnrealNetwork.h"
#include "EO_Stove.h"

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

	space = Cast<UH_OverkasePlayerMove>(me->overPlayerMove);
	
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

	if (!bPressedCtrl)
	{
		bIsDoingInteraction = false;
	}
	if (blockActor.IsEmpty() == false) {
		if (bIsDoingInteraction)
		{
			SetOwnerToActor(block);
			
			if (Cast<AEO_ChopTable>(block))
			{
			Cast<AEO_ChopTable>(block)->ServerInteraction2();

			}
			else
			{
				block->ServerInteraction();
			}

			if (blockActor[closestBlockIndex]->GetName().Contains(FString("Sink")))
			{
				
				GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Emerald, FString::Printf(TEXT("%s"), *blockActor[closestBlockIndex]->GetName()));
				if (!bIsInteraction) {
					//WashHand();
				}
				
			}
			else if (blockActor[closestBlockIndex]->GetName().Contains(FString("ChopTable")))
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Cyan, FString::Printf(TEXT("%s"), *blockActor[closestBlockIndex]->GetName()));
				if (!bIsInteraction) {
					//ChopHand();
				}
				if (!me->bSoundPlay) {
					SoundPlay();
				}
			}

		}
		else if (!bIsDoingInteraction && blockActor[closestBlockIndex]->GetName().Contains(FString("Sink")))
		{
			/*me->AnimationComponent->CallWashHand(false);
			me->AnimationComponent->DownHand();*/
			bIsInteraction = false;
		}
		else if (!bIsDoingInteraction && blockActor[closestBlockIndex]->GetName().Contains(FString("ChopTable")))
		{
			/*me->AnimationComponent->CallChopHand(false);
			me->AnimationComponent->DownHand();*/
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
	//���ڽ��� ��ǲ ���ε�
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (pInput) 
	{
		pInput->BindAction(ia_Space_Interaction, ETriggerEvent::Triggered, this, &UH_OverkaseInteraction::ServerSpaceInput);
		pInput->BindAction(ia_ctrl_Interaction, ETriggerEvent::Started, this, &UH_OverkaseInteraction::ServerCtrlInput);
		pInput->BindAction(ia_ctrl_Interaction, ETriggerEvent::Completed, this, &UH_OverkaseInteraction::ServerCtrlCompleted);

	}
	
}

void UH_OverkaseInteraction::ServerSpaceInput_Implementation()
{	
	MulticastSpaceInput();
}

void UH_OverkaseInteraction::MulticastSpaceInput_Implementation()
{
	SetOwnerToActor(me);
	
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
		ServerItemOnPlayer();
		me->MulticastOnPickUpSound();

	}
	// ���� �������� ���� ��ó�� Ǫ�尡 ������
	else if (!bHasItem && !foodDistance.IsEmpty())
	{
		//Ǫ�带 �����Ͷ�
		ServerGetFood(me->interactionPosition);
		me->MulticastOnPickUpSound();

	}
	// ���� �������� ���� ����� �Ÿ��� Ǫ���� �Ÿ����� ������
	else if (!bHasItem && blockDistance[closestBlockIndex] < foodDistance[closestFoodIndex])
	{
		// ����� �����Ͷ�
		ServerItemOnPlayer();
		//UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);
		me->MulticastOnPickUpSound();

	}
	// ���� �������� ���� Ǫ���� �Ÿ��� ����� �Ÿ����� ������
	else if (!bHasItem && blockDistance[closestBlockIndex] > foodDistance[closestFoodIndex])
	{
		//Ǫ�带 �����Ͷ�
		ServerGetFood(me->interactionPosition);
		//UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);

	}
	// �������� ������
	else
	{
		// �տ� ����� �������ƶ�
		ServerNoItem();
		//UGameplayStatics::PlaySound2D(GetWorld(), putDownSound);
		me->MulticastOnPickUpSound();
	}
}

void UH_OverkaseInteraction::ServerCtrlInput_Implementation()
{
	MulicastCtrlInput();
}

void UH_OverkaseInteraction::MulicastCtrlInput_Implementation()
{
	bPressedCtrl = true;

	if (bHasItem)
	{
		AEO_Food* food = Cast<AEO_Food>(items[0]);
		if (!items.IsEmpty()) {
			if (items[0] == food)
			{
				items[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				Food->ShootFood(me->GetActorForwardVector());
				me->MulticastOnThrowSound();

			}
		}
	}
	else if (block != nullptr && block->bIsInterObj)
	{
		bIsDoingInteraction = true;
	}
}

void UH_OverkaseInteraction::ServerItemOnPlayer_Implementation()
{
	MulticastItemOnPlayer();
}

void UH_OverkaseInteraction::MulticastItemOnPlayer_Implementation()
{
	if (!bHasItem)
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
				SetOwnerToActor(block);
				block->ServerGetItem(me->interactionPosition);
				//block->GetItem(me->interactionPosition);

				if (items.IsEmpty() == false)
				{
					//bHasItem = true;
				}

				/*FTimerHandle getHandler;
				GetWorld()->GetTimerManager().SetTimer(getHandler, FTimerDelegate::CreateLambda([&]() {block->ServerGetItem(me->interactionPosition); }), 0.3f, false);*/
			}
		}
	}
}

void UH_OverkaseInteraction::ServerNoItem_Implementation()
{
	if (Food)
	{
		
	}
	if (bHasItem) {
		// ���� ��ó�� ����� ���ٸ�
		if (blockActor.IsEmpty())
		{
			// ���� 0���� �ִٸ�
			if (items.IsValidIndex(0))
			{
				Food->DropItem();
				// �������� �������ƶ�
				items[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				me->MulticastOnPutDownSound();
			}
			//bHasItem = false;
		}
		else
		{
			if (!items.IsEmpty())
			{
				SetOwnerToActor(block);
				if (Cast<AEO_ChopTable>(block))
				{
				Cast<AEO_ChopTable>(block)->ServerOnItem2(items[0]);
				}
				else if (Cast<AEO_Stove>(block))
				{
					Cast<AEO_Stove>(block)->ServerOnItem2(items[0]);
				}
				else
				{
					block->ServerOnItem(items[0]);
				}
				if (items.IsEmpty())
				{
					//bHasItem = false;
					me->MulticastOnPutDownSound();

				}
			}
		}
	}
}

void UH_OverkaseInteraction::MulticastNoItem_Implementation()
{
	//AEO_Plate* plate = Cast<AEO_Plate>(items[0]);
		//AEO_Pot* pot = Cast<AEO_Pot>(items[0]);

		// ���� �������� �տ� ���������
	
}

void UH_OverkaseInteraction::ServerCtrlCompleted_Implementation()
{
	bPressedCtrl = false;
}

void UH_OverkaseInteraction::SoundPlay()
{
	me->MulticastOnChopSound();
}

void UH_OverkaseInteraction::SetOwnerToActor_Implementation(class AActor* sibling)
{
	sibling->SetOwner(me);
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
		//UE_LOG(LogTemp,Warning, TEXT("GetFood"));
		foodActor.Remove(food);
		foodDistance.RemoveAt(0);
	}
}

void UH_OverkaseInteraction::ServerGetFood_Implementation(class USceneComponent* playerSceneComp)
{
	
	Food = Cast<AEO_Food>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Food::StaticClass()));

	SetOwnerToActor(Food);
	UE_LOG(LogTemp, Warning, TEXT("Food Connection : %s"), Food->GetNetConnection() == nullptr?TEXT("NULL"):TEXT("Valid"));
	if (GetNetMode() == NM_Client)
	{
	}

	if (Food)
	{
		if (!bHasItem)
		{
			if (foodActor.IsEmpty()) {
				return;
			}

			foodActor[closestFoodIndex]->PickUpItem();
			foodActor[closestFoodIndex]->AttachToComponent(playerSceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			bHasItem = true;
		}
	}
	//MulticastGetFood(playerSceneComp);
}


void UH_OverkaseInteraction::MulticastGetFood_Implementation(class USceneComponent* playerSceneComp)
{
		UE_LOG(LogTemp, Warning, TEXT("PC : %s, netmode : %d"), me->Controller == nullptr?TEXT("NULL"):TEXT("valid"), GetNetMode());
	
}

void UH_OverkaseInteraction::ServerWashHand_Implementation()
{
	bIsInteraction = true;
	//me->AnimationComponent->CallWashHand(true);
}

void UH_OverkaseInteraction::ServerChopHand_Implementation()
{
	bIsInteraction = true;
	//me->AnimationComponent->CallChopHand(true);
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


//void UH_OverkaseInteraction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(UH_OverkaseInteraction, foodActor);
//}
