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

	//�뽬�߿��� �뽬Ű�� ��Ȱ��ȭ ��Ű�� �ʹ�.
		// 1. �뽬������ �ƴ��� �˰�ʹ�.
	
	if (bIsDash) {
		// 2. �뽬���̸� ��ǲ���� �����ʴ´�
		UE_LOG(LogTemp,Warning,TEXT("in"));
		moveComp->MaxWalkSpeed = FMath::Lerp(1500, 350, 0.2f);
	}

	if (currentTime > 0.3) {
		moveComp->MaxWalkSpeed = 400;
		bIsDash = false;
		
	}
	//if (moveComp->MaxWalkSpeed < 450) {
	//	// 3. �ӵ��� 400 ��ó���Ǹ� �ӵ��� 400���� �ٲ۴�
	//	bIsDash = false;
	//	moveComp->MaxWalkSpeed = 400;
	//}
}

void UH_OverkasePlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//Input Action�� ó���� �Լ��� ���ε� ���ֱ�
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
		// 3. �뽬���̾ƴϸ� �뽬�� �Ѵ�.
		bIsDash = true;
		currentTime = 0;

	}
}
