// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverkasePlayerBase.h"
#include "EO_Food.h"
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
	UFUNCTION(Server, Unreliable)
	void ServerSpaceInput();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSpaceInput();

	UFUNCTION(Server, Unreliable)
	void ServerCtrlInput();

	UFUNCTION(NetMulticast, Unreliable)
	void MulicastCtrlInput();

	UFUNCTION(Server, Unreliable)
	void ServerItemOnPlayer();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastItemOnPlayer();

	UFUNCTION(Server, Unreliable)
	void ServerNoItem();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastNoItem();

	UFUNCTION(Server, Unreliable)
	void ServerCtrlCompleted();

	UFUNCTION(Server, Unreliable)
	void ServerGetFood(class USceneComponent* playerSceneComp);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastGetFood(class USceneComponent* playerSceneComp);

	UFUNCTION(Server, Unreliable)
	void ServerWashHand();

	UFUNCTION(Server, Unreliable)
	void ServerChopHand();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Space_Interaction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_ctrl_Interaction;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* pickUpSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* putDownSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* throwSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* chopSound;

	UPROPERTY(EditAnywhere, Category = "Foods")
	TArray<AEO_Block*> blockActor;
	UPROPERTY(EditAnywhere, Category = "Foods")
	TArray<float> blockDistance;

	UPROPERTY(EditAnywhere, Category = Foods)
	TArray<AEO_Food*> foodActor;

	UPROPERTY(EditAnywhere, Category = Foods)
	bool bHasItem = false;

	TArray<float> foodDistance;


	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	class UH_OverkasePlayerMove* space;

public:
	bool bClickedSpace = false;
	bool bIsDoingInteraction = false;
	bool bPressedCtrl = false;
	bool bSoundPlay = false;
	//UPROPERTY(Replicated)
	bool bIsInteraction = false;
private:

	int32 FindClosestBlock();
	int32 FindClosestFood();

	void SoundPlay();

	int32 closestFoodIndex = 0;
	int32 closestBlockIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category=settings)
	TArray<AActor*> items;

	UFUNCTION(Server, Reliable)
	void SetOwnerToActor(class AActor* sibling);
};
