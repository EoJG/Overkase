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

	class UH_OverkaseInteraction* inter;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* sizzleSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* serviceSound;
public:
	UPROPERTY(VisibleAnywhere, Category = "Check")
	bool bCanCook = false;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void GetItem(class USceneComponent* playerSceneComp);

	void StartSizzleSound();
	void StopSizzleSound();
	
	UFUNCTION(Server, Reliable)
	void ServerOnServiceSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnServiceSound();

	UFUNCTION(Server, Reliable)
	void ServerOnItem2(class AActor* item);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnItem2(class AActor* item);

	UFUNCTION(Server, Reliable)
	void ServerOnIteminTick(float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnIteminTick(float DeltaTime);

	virtual void ServerGetItem(class USceneComponent* playerSceneComp) override;
	virtual void MulticastGetItem(class USceneComponent* playerSceneComp) override;
};
