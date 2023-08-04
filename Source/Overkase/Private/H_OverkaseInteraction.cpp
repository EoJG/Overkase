// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseInteraction.h"
#include "EO_Block.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>

UH_OverkaseInteraction::UH_OverkaseInteraction()
{

}

void UH_OverkaseInteraction::BeginPlay()
{
	Super::BeginPlay();
	
}

void UH_OverkaseInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* ClosestActor = FindClosestActor();

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

AActor* UH_OverkaseInteraction::FindClosestActor()
{
	AActor* ClosestActor = nullptr;
	//float ShortestDistance = TNumericLimits<float>::Max(); // Set initial shortest distance to a high value

	for (int i=0;i<foodActor.Num();i++)
	{
		float dist = FVector::Distance(me->GetActorLocation(),foodActor[i]->GetActorLocation());
		floatDistance[i] = dist;
		floatDistance.M
		//if (Actor)
		//{
		//	
		//	/*float Distance = FVector::Distance(me->GetActorLocation(), Actor->GetActorLocation());
		//	if (Distance < ShortestDistance)
		//	{
		//		ShortestDistance = Distance;
		//		ClosestActor = Actor;
		//	}*/
		//}
	}

	return ClosestActor;
}
