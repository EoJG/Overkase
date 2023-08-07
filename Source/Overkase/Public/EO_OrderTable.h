// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_OrderTable.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_OrderTable : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_OrderTable(); 

protected:
		virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AEO_ReturnPlate> returnPlate;
	UPROPERTY(VisibleAnywhere)
	class AEO_ReturnPlate* wReturnPlate;

public:
	virtual void OnItem(class AActor* item) override;
};
