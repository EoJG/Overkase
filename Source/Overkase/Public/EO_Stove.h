// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_Stove.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_Stove : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_Stove();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	class AEO_Food* sFoodTemp;

public:
	UPROPERTY(VisibleAnywhere, Category = "Check")
	bool bCanCook = false;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void GetItem(class USceneComponent* playerSceneComp);

	virtual void ServerOnItem(class AActor* item) override;
	virtual void MulticastOnItem(class AActor* item) override;

	virtual void ServerGetItem(class USceneComponent* playerSceneComp) override;
	virtual void MulticastGetItem(class USceneComponent* playerSceneComp) override;
};
