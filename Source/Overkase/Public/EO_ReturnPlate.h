// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_ReturnPlate.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_ReturnPlate : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_ReturnPlate();

public:
	UPROPERTY(VisibleAnywhere, Category="Settings")
	TSubclassOf<class AEO_Plate> rPlate;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void GetItem(class USceneComponent* playerSceneComp) override;
	void SpawnPlate();

	virtual void ServerOnItem(class AActor* item) override;
	//virtual void MulticastOnItem(class AActor* item) override;

	virtual void ServerGetItem(class USceneComponent* playerSceneComp) override;
	virtual void MulticastGetItem(class USceneComponent* playerSceneComp) override;

	UFUNCTION(Server, Reliable)
	void ServerSpawnPlate();

	float plateCount = 0;
};
