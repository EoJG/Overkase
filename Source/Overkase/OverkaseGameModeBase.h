// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OverkaseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AOverkaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite, Category = Time)
	float Seconds = 30;
	UPROPERTY(BlueprintReadWrite, Category = Time)
	float Minutes = 3;
		

};
