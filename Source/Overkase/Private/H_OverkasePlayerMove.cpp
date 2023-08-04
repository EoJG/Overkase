// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkasePlayerMove.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>


UH_OverkasePlayerMove::UH_OverkasePlayerMove()
{


}

void UH_OverkasePlayerMove::BeginPlay()
{
	Super::BeginPlay();
	
	moveComp->MaxWalkSpeed = 400;



}

void UH_OverkasePlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentTime += DeltaTime;

	//대쉬중에는 대쉬키를 비활성화 시키고 싶다.
		// 1. 대쉬중인지 아닌지 알고싶다.
	
	if (bIsDash) {
		// 2. 대쉬중이면 인풋값을 받지않는다
		UE_LOG(LogTemp,Warning,TEXT("in"));
		moveComp->MaxWalkSpeed = FMath::Lerp(1500, 350, 0.2f);
	}

	if (currentTime > 0.3) {
		moveComp->MaxWalkSpeed = 400;
		bIsDash = false;
		
	}
	//if (moveComp->MaxWalkSpeed < 450) {
	//	// 3. 속도가 400 근처가되면 속도를 400으로 바꾼다
	//	bIsDash = false;
	//	moveComp->MaxWalkSpeed = 400;
	//}
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
	
	if (!bIsDash) {
		// 3. 대쉬중이아니면 대쉬를 한다.
		bIsDash = true;
		currentTime = 0;

	}
}
