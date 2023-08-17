// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_FoodBox.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_FoodBox : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_FoodBox();

public:
	UPROPERTY(EditAnywhere, Category="Settings")
	TSubclassOf<class AEO_Food> food;

public:
	virtual void GetItem(class USceneComponent* playerSceneComp) override;

	virtual void ServerGetItem(class USceneComponent* playerSceneComp) override;
	virtual void MulticastGetItem(class USceneComponent* playerSceneComp) override;
};
