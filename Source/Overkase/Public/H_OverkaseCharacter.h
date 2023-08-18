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

	UFUNCTION(NetMulticast, Reliable)
	void SendMulticast(int32 random);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handR;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handL;


	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* crocodileMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* headComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* hatComp;
	UPROPERTY(EditAnywhere)
	class USphereComponent* interationDistance;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* interactionPosition;

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
	UPROPERTY(EditDefaultsOnly, Category = Effect )
	class UParticleSystem* effect;

	UPROPERTY(VisibleAnywhere, Category = "EO")
	TSubclassOf<class UEO_InGameInterface> inGameUIClass;
	UPROPERTY(VisibleAnywhere, Category = "EO")
	class UEO_InGameInterface* inGameUI;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnParticle();

	UPROPERTY(Replicated)
	float currentTime = 0;

	void spawn();
};
