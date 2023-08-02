// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverkasePlayerBase.h"
#include "H_OverkasePlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UH_OverkasePlayerMove : public UOverkasePlayerBase
{
public:

	UH_OverkasePlayerMove();
	GENERATED_BODY()
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;
	
	bool bIsDash = false;

	float currentTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_dash;

	//�¿��̵�
	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void DashMove();
};
