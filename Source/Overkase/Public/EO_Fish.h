// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Food.h"
#include "EO_Fish.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_Fish : public AEO_Food
{
	GENERATED_BODY()
	
public:
	AEO_Fish();

protected:
	virtual void BeginPlay() override;
};
