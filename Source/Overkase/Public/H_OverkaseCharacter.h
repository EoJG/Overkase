// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H_OverkaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegete, class UInputComponent*);


UCLASS()
class OVERKASE_API AH_OverkaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AH_OverkaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// delegate
	FInputBindingDelegete onInputBindingDelegate;

	// Move Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UOverkasePlayerBase* overPlayerMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UOverkasePlayerBase* overPlayerInteraction;

	//Enhanced Input resources
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc;
	
};
