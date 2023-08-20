// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkasePlayerMove.h"
#include "H_OverkaseInteraction.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_PlayerCameraActor.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>


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
	

	

}

void UH_OverkasePlayerMove::BeginPlay()
{
	Super::BeginPlay();
	
	moveComp->MaxWalkSpeed = 600;

}

void UH_OverkasePlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentTime += DeltaTime;

	if (bIsDash) {
		// 2. 대쉬중이면 인풋값을 받지않는다
		//UE_LOG(LogTemp,Warning,TEXT("in"));
		moveComp->MaxWalkSpeed = FMath::Lerp(2000, 350, 0.2f);
	}

	if (currentTime > 0.3) {
		moveComp->MaxWalkSpeed = 600;
		//me->ServerEndVFX();
		bIsDash = false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Emerald, FString::Printf(TEXT("%f"), me->GetCharacterMovement()->Velocity.Length()));
	if (me->GetCharacterMovement()->Velocity.Length() > 0) 
	{
		bIsWalk = true;
	}
	else 
	{
		bIsWalk = false;
	}

	space = Cast<UH_OverkaseInteraction>(me->overPlayerInteraction);

	//애니메이션 if문
	if (bIsWalk && space->bHasItem == false)
	{
		//me->AnimationComponent->CallWalk(true);
	}
	else if (bIsWalk && space->bHasItem == true)
	{
		//me->AnimationComponent->UpHand();
	}
	else if(!bIsWalk && space->bHasItem == false)
	{
		/*me->AnimationComponent->CallWalk(false);
		me->AnimationComponent->DownHand();*/
	}
	else if (!bIsWalk && space->bHasItem == true)
	{
		//me->AnimationComponent->UpHand();
	}


}

void UH_OverkasePlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	auto pInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//Input Action을 처리할 함수와 바인딩 해주기
	if (pInput) {
	
		pInput->BindAction(ia_move, ETriggerEvent::Triggered, this, &UH_OverkasePlayerMove::Move);
		pInput->BindAction(ia_dash, ETriggerEvent::Triggered, this, &UH_OverkasePlayerMove::ServerDashMove);

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

void UH_OverkasePlayerMove::ServerDashMove_Implementation()
{
	if (!bIsDash) {
		UE_LOG(LogTemp, Warning, TEXT("ServerVFX"));

		me->MulticastOnDashSound();
		//me->MulticastOnParticle();
		me->MulticastOnVFX();
		// 3. 대쉬중이아니면 대쉬를 한다.
		bIsDash = true;
		currentTime = 0;

	}
}



