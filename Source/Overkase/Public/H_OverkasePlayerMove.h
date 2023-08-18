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

	GENERATED_BODY()
		UH_OverkasePlayerMove();


	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

public:
	//Enhanced Input sources
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_dash;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* dashSound;

	

	UPROPERTY(VisibleAnywhere)
	class UH_OverkaseInteraction* space;
	//좌우이동
	UFUNCTION()
	void Move(const FInputActionValue& value);

	//대쉬
	UFUNCTION(Server, UnReliable)
	void ServerDashMove();


	bool bIsWalk = false;
private:
	bool bIsDash = false;
	
	float currentTime = 0;

};
