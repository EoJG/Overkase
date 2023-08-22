// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_Menu.generated.h"


UCLASS()
class OVERKASE_API UEO_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UProgressBar* progress_Timer;

public:
	UPROPERTY()
	float curTime;
	UPROPERTY()
	float coolTime = 30;//120;

public:
	UFUNCTION()
	void BindPercent();
	UFUNCTION()
	void TimeOver();
};
