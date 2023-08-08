// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Food.h"
#include "EO_FishSushi.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_FishSushi : public AEO_Food
{
	GENERATED_BODY()
	
public:	 
	AEO_FishSushi();

protected:
	virtual void BeginPlay() override;
};
