// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkasePlayerMove.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>


UH_OverkasePlayerMove::UH_OverkasePlayerMove()
{
	//moveComp->MaxWalkSpeed = 400;

}

void UH_OverkasePlayerMove::BeginPlay()
{
	Super::BeginPlay();
	


}

void UH_OverkasePlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentTime += DeltaTime;

	if (currentTime > 0.5f) {
		bIsDash = false;
	}
	
}

void UH_OverkasePlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//Input Action을 처리할 함수와 바인딩 해주기
	if (pInput) {
		pInput->BindAction(ia_move, ETriggerEvent::Triggered, this, &UH_OverkasePlayerMove::Move);
		pInput->BindAction(ia_dash, ETriggerEvent::Triggered, this, &UH_OverkasePlayerMove::DashMove);
	}
	
}

void UH_OverkasePlayerMove::Move(const FInputActionValue& value)
{
	FVector2D mValue = value.Get<FVector2D>();
	me->AddMovementInput(me->GetActorRightVector(), mValue.X);
	me->AddMovementInput(me->GetActorForwardVector(), mValue.Y);
}

void UH_OverkasePlayerMove::DashMove()
{
	
	bIsDash = true;
	if (bIsDash) {
	//moveComp->MaxWalkSpeed = 1000;
	}
	else {
		//moveComp->MaxWalkSpeed = 400;
	}
	
}
