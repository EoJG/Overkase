// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EO_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	AEO_PlayerController();
	virtual void BeginPlay() override;

public:
	virtual void PreClientTravel(const FString& PendingURL, ETravelType TravelType, bool bIsSeamlessTravel) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UH_OverLoginWidget> loginSub;
	UPROPERTY()
	class UH_OverLoginWidget* loginWidget;
};
