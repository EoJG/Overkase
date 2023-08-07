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
	TSubclassOf<class AEO_Plate> plate;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void GetItem(class USceneComponent* playerSceneComp) override;
	void SpawnPlate();
};
