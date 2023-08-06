// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseInteraction.h"
#include "EO_Block.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

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

	
	closestBlockIndex = FindClosestActor();
	if (foodActor.Num() != 0) {
	block = Cast<AEO_Block>(foodActor[closestBlockIndex]);

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
	if (!bHasItem) {
		ItemOnPlayer();
	}
	else {
		NoItem();
	}
}

void UH_OverkaseInteraction::CtrlInput()
{
	
}

void UH_OverkaseInteraction::ItemOnPlayer()
{
	block->GetItem(me->interactionPosition);
	bHasItem = true;
}

void UH_OverkaseInteraction::NoItem()
{

	TArray<AActor*> items;
	me->GetAttachedActors(items);

	//items[0]
	block->OnItem(items[0]);
	bHasItem = false;
}

void UH_OverkaseInteraction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEO_Block* temp = Cast<AEO_Block>(OtherActor))
	{
		foodActor.Add(temp);
		floatDistance.Add(0);
	}
}

void UH_OverkaseInteraction::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEO_Block* temp = Cast<AEO_Block>(OtherActor))
	{
		foodActor.Remove(temp);
		floatDistance.Remove(0);
	}
	
}

int32 UH_OverkaseInteraction::FindClosestActor()
{

	int32 ClosestIndex = 0; // Initialize with an invalid index
	 
	float ShortestDistance = TNumericLimits<float>::Max(); // shortestDistance 를 최대값으로 만듦

	for (int32 i = 0; i < foodActor.Num(); ++i)
	{
		// 나와  i번째 foodActor 의 거리를 floatDistance 의 i번째에 저장
		floatDistance[i] = FVector::Dist(me->GetActorLocation(), foodActor[i]->GetActorLocation());

		float dist = floatDistance[i]; // i번째 거리를 dist 에 저장

		//만약 dist 가 ShortestDistance 보다 작다면
		if (dist < ShortestDistance)
		{
			ShortestDistance = dist; // ShortestDistance 는 Dist로 저장
			ClosestIndex = i; // dist 가 제일 짧다면 i 는 제일 가까운 인덱스 번호
		}
	}

	return ClosestIndex; // 제일 가까운 인덱스 번호를 저장
}
