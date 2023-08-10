// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Count.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UUI_Count : public UUserWidget
{
	GENERATED_BODY()
	

public:
	// Ÿ�̸� ī��Ʈ (��) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_MinCount;
	
	// Ÿ�̸� ī��Ʈ (��) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_SecCount;

	// Ÿ�̸� ī��Ʈ (:) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* edit_TimerCount;


	UPROPERTY(BlueprintReadWrite, Category = minuteTime)
	float MinTime = 03;

	UPROPERTY(BlueprintReadWrite, Category = secondTime)
	float SecTime = 30;

	UPROPERTY(BlueprintReadOnly)
	float CurrentTime = 0;
	

	void GetMin();
	void GetSec();





};
