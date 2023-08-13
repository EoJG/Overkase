// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkasePlayerMove.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_PlayerCameraActor.h"
#include <Kismet/GameplayStatics.h>


UH_OverkasePlayerMove::UH_OverkasePlayerMove()
{
	ConstructorHelpers::FObjectFinder<UInputAction> TempMove (TEXT("/Script/EnhancedInput.InputAction'/Game/HanSeunghui/Input/IA_OverkaseMove.IA_OverkaseMove'"));
	if (TempMove.Succeeded())
	{
		ia_move = TempMove.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> TempDash(TEXT("/Script/EnhancedInput.InputAction'/Game/HanSeunghui/Input/IA_OverkaseDash.IA_OverkaseDash'"));
	if (TempDash.Succeeded())
	{
		ia_dash = TempDash.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempSound(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Dash1.Dash1'"));
	if (TempSound.Succeeded())
	{
		dashSound = TempSound.Object;
	}


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

	if (bIsDash) {
		// 2. �뽬���̸� ��ǲ���� �����ʴ´�
		UE_LOG(LogTemp,Warning,TEXT("in"));
		moveComp->MaxWalkSpeed = FMath::Lerp(1500, 350, 0.2f);
	}

	if (currentTime > 0.3) {
		moveComp->MaxWalkSpeed = 400;
		bIsDash = false;
		
	}
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
		FVector rightVectorOfController = FRotationMatrix(me->GetControlRotation()).GetUnitAxis(EAxis::Y);
		FVector forwardVectorOfController = FRotationMatrix(me->GetControlRotation()).GetUnitAxis(EAxis::X);
		me->AddMovementInput(rightVectorOfController, mValue.X);
		me->AddMovementInput(forwardVectorOfController, mValue.Y);
	
}

void UH_OverkasePlayerMove::DashMove()
{
	
	if (!bIsDash) {
		UGameplayStatics::PlaySound2D(GetWorld(), dashSound);
		// 3. �뽬���̾ƴϸ� �뽬�� �Ѵ�.
		bIsDash = true;
		currentTime = 0;

	}
}
