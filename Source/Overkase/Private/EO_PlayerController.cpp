// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_PlayerController.h"
#include "H_OverLoginWidget.h"

AEO_PlayerController::AEO_PlayerController()
{
	
}

void AEO_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	loginWidget = Cast<UH_OverLoginWidget>(CreateWidget(GetWorld(), loginSub));
	loginWidget->AddToViewport();
}

void AEO_PlayerController::PreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel)
{
	Super::PreClientTravel(PendingURL, TravelType, bIsSeamlessTravel);

	loginWidget->PlayAnimation(loginWidget->fadeOutAnim);
}
