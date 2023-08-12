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
	void SpaceInput();
	void CtrlInput();
	void ItemOnPlayer();
	void NoItem();
	void CtrlCompleted();
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Space_Interaction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_ctrl_Interaction;
	

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

	void GetFood(class USceneComponent* playerSceneComp);
	void ReleaseFood(class AActor* food);


private:
	bool bClickedSpace = false;
	bool bIsDoingInteraction = false;
	bool bPressedCtrl = false;
private:

	int32 FindClosestBlock();
	int32 FindClosestFood();

	int32 closestFoodIndex = 0;
	int32 closestBlockIndex = 0;

	TArray<AActor*> items;
};
