// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_Sink.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_Sink : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_Sink();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class AEO_Plate> plate;

private:
	int plateCount = 0;
	int compleCount = 0;
	float curTime = 0;
	float coolTime = 3;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void GetItem(class USceneComponent* playerSceneComp) override;
	virtual void Interaction() override;
	void SpawnPlate();

	virtual void ServerOnItem(class AActor* item) override;
	virtual void MulticastOnItem(class AActor* item) override;

	virtual void ServerGetItem(class USceneComponent* playerSceneComp) override;
	virtual void MulticastGetItem(class USceneComponent* playerSceneComp) override;

	virtual void ServerInteraction() override;
	virtual void MulticastInteraction() override;

	UFUNCTION(Server, Reliable)
	void ServerSpawnPlate();

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class UAudioComponent* washSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* dishSound;

	UFUNCTION(Server, Reliable)
	void ServerOnDishSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDishSound();
};
