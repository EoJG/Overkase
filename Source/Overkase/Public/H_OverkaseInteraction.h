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
	UH_OverkaseInteraction();

protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

public:
	void SpaceInput();
	void CtrlInput();
	void ItemOnPlayer();
	void NoItem();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Space_Interaction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_ctrl_Interaction;

private:
	bool bClickedSpace = false;
	bool bHasItem = false;
};
