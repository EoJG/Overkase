// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EO_Block.h"
#include "EO_TrashCan.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_TrashCan : public AEO_Block
{
	GENERATED_BODY()
	
public:
	AEO_TrashCan();

public:
	virtual void OnItem(class AActor* item);
};
