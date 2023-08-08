// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseInteraction.h"
#include "EO_Block.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>



UH_OverkaseInteraction::UH_OverkaseInteraction()
{

}

void UH_OverkaseInteraction::BeginPlay()
{
	Super::BeginPlay();
	me->interationDistance->OnComponentBeginOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentBeginOverlap);
	me->interationDistance->OnComponentEndOverlap.AddDynamic(this, &UH_OverkaseInteraction::OnComponentEndOverlap);

}

void UH_OverkaseInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	closestBlockIndex = FindClosestBlock();
	if (blockActor.Num() != 0) {
	block = Cast<AEO_Block>(blockActor[closestBlockIndex]);

	}
	closestFoodIndex = FindClosestFood();
	if (foodActor.Num() != 0)
	{
		Food = Cast<AEO_Food>(foodActor[closestFoodIndex]);
	}
}

void UH_OverkaseInteraction::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{	
	//인핸스드 인풋 바인딩
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (pInput) 
	{
		pInput->BindAction(ia_Space_Interaction, ETriggerEvent::Triggered, this, &UH_OverkaseInteraction::SpaceInput);
		pInput->BindAction(ia_ctrl_Interaction, ETriggerEvent::Triggered, this, &UH_OverkaseInteraction::CtrlInput);

	}
	
}

void UH_OverkaseInteraction::SpaceInput()
{
	if (!bHasItem && !blockDistance.IsEmpty()) {
		ItemOnPlayer();
	}
	else if (!bHasItem && !foodDistance.IsEmpty()) {
		GetFood(me->interactionPosition);
	}
	else if (!bHasItem && blockDistance[closestBlockIndex] > foodDistance[closestFoodIndex])
	{
		ItemOnPlayer();
	}
	else if (!bHasItem && blockDistance[closestBlockIndex] < foodDistance[closestFoodIndex]) {
		GetFood(me->interactionPosition);
	}
	else
	{
		NoItem();
	}
}

void UH_OverkaseInteraction::CtrlInput()
{
	
}

void UH_OverkaseInteraction::ItemOnPlayer()
{
	//블록 이근처에 없으면
	if (blockActor.IsEmpty()) {
	// 그냥넘어가라
		return;
	}
	else {
	// 블록을 든다
	block->GetItem(me->interactionPosition);
	bHasItem = true;
	}
}

void UH_OverkaseInteraction::NoItem()
{
	TArray<AActor*> items;
	me->GetAttachedActors(items);

	if (blockActor.IsEmpty())
	{
		if (items.IsValidIndex(0))
		{
			items[0]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		bHasItem = false;
		//bHasFood = false;
	}
	else
	{
		if (items.IsEmpty() == false) 
		{
			block->OnItem(items[0]);
			bHasItem = false;
			//bHasFood = false;
		}
	}
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
		blockDistance.Remove(0);
	}

	if (AEO_Food* food = Cast<AEO_Food>(OtherActor))
	{
		foodActor.Remove(food);
		foodDistance.Remove(0);
	}
}

void UH_OverkaseInteraction::GetFood(class USceneComponent* playerSceneComp)
{
	Food = Cast<AEO_Food>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Food::StaticClass()));
	if (Food)
	{
		if (!bHasItem)
		{
			
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
