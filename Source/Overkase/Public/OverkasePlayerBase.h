// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "H_OverkaseCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "OverkasePlayerBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERKASE_API UOverkasePlayerBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOverkasePlayerBase();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AH_OverkaseCharacter* me;

	UPROPERTY()
	UCharacterMovementComponent* moveComp;

	UPROPERTY()
	class AEO_Block* block;

	UPROPERTY()
	class AEO_Food* Food;
		
public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {}
};
