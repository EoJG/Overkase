// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_ChopTable.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_ChopTable : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_ChopTable();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* boardComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* knifeComp;

private:
	class AEO_Food* food = nullptr;

public:
	virtual void OnItem(class AActor* item) override;
	virtual void Interaction() override;

	UFUNCTION(Server, Unreliable)
	void ServerOnItem2(class AActor* item);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastOnItem2(class AActor* item);

	UFUNCTION(Server, Unreliable)
	void ServerInteraction2();
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastInteraction2();
};
