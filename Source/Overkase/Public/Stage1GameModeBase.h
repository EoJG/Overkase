// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Stage1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AStage1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStage1GameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category="WidgetSettings")
	TSubclassOf<class UEO_InGameInterface> menuInterface;
	UPROPERTY(VisibleAnywhere, Category="WidgetSettings")
	TSubclassOf<class AEO_OrderTable> orderTable;
};
