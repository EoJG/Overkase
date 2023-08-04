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
