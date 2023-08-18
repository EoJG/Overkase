// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EO_LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API AEO_LobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	AEO_LobbyGameModeBase();
	virtual void Tick(float DeltaSeconds) override;
};
