// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "H_OverGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UH_OverGameInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UH_OverGameInstance();

	virtual void Init() override;

public:
	FString overSessionName;

	IOnlineSessionPtr sessionInterface;

public:
	void CreateMySession();

	void OnCreateMySession(FName sessionName, bool bWasSuccessful);
};
