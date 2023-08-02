// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkasePlayerMove.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>


void UH_OverkasePlayerMove::BeginPlay()
{
	Super::BeginPlay();



}

void UH_OverkasePlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UH_OverkasePlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//Input Action을 처리할 함수와 바인딩 해주기
	if (pInput) {
		pInput->BindAction(ia_move, ETriggerEvent::Triggered, this, &UH_OverkasePlayerMove::Move);
	}
	
}

void UH_OverkasePlayerMove::Move(const FInputActionValue& value)
{
	FVector2D mValue = value.Get<FVector2D>();
	me->AddMovementInput(me->GetActorRightVector(), mValue.X);
	me->AddMovementInput(me->GetActorForwardVector(), mValue.Y);
}
