// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverkasePlayerBase.h"
#include "H_OverkaseInteraction.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UH_OverkaseInteraction : public UOverkasePlayerBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

	void InterActionInput();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Space_Interaction;
};
