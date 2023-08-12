// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_AnimationComponent.h"

// Sets default values for this component's properties
UEO_AnimationComponent::UEO_AnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEO_AnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	headMesh = Cast<UStaticMeshComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Head")));
	handComp = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Hand")));
	handRComp = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("HandRComp")));
	handRMesh = Cast<UStaticMeshComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Hand_R")));
	handLMesh = Cast<UStaticMeshComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("Hand_L")));
}
	

// Called every frame
void UEO_AnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ChopHand();
	WashHand();
}

void UEO_AnimationComponent::UpHand()
{
	handComp->SetRelativeLocationAndRotation(FVector(100, 0, 0), FRotator(90, 0, 0));
}

void UEO_AnimationComponent::DownHand()
{
	handComp->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0, 0, 0));
}

void UEO_AnimationComponent::CallChopHand(bool playAnimation)
{
	isPlayChopHand = playAnimation;

	if (playAnimation == false)
		bDoOnce = true;
}

void UEO_AnimationComponent::CallWashHand(bool playAnimation)
{
	isPlayWashHand = playAnimation;

	if (playAnimation == false)
		bDoOnce = true;
}

void UEO_AnimationComponent::ChopHand()
{
	if (isPlayChopHand)
	{
		if (bDoOnce)
		{
			handRComp->SetRelativeRotation(FRotator(80, 0, 0));
			bDoOnce = false;
		}

		if (handRComp->GetRelativeRotation().Pitch >= 80)
		{
			c = 10;
		}
		else if (handRComp->GetRelativeRotation().Pitch <= -10)
		{
			c = -10;
		}

		handRComp->AddWorldRotation(FRotator(c, 0, 0));
	}
}

void UEO_AnimationComponent::WashHand()
{
	if (isPlayWashHand)
	{
		time += GetWorld()->DeltaTimeSeconds * 20;
		if (time >= 360)
			time = 0;

		if (bDoOnce)
		{
			handComp->SetRelativeLocationAndRotation(FVector(100, 0, 0), FRotator(90, 0, 0));
			bDoOnce = false;
		}

		float a = FMath::Cos(time) * 10;
		float b = FMath::Sin(time) * 10;
		FVector vec = FVector(a, 0, -b);

		handRMesh->SetRelativeLocation(handRMesh->GetRelativeLocation() + vec);
	}
}

