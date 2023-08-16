// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_InGameInterface.generated.h"


UCLASS()
class OVERKASE_API UEO_InGameInterface : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UTextBlock* text_Minute;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UTextBlock* text_Second;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UProgressBar* progress_Timer;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="ScoreSettings")
	class UTextBlock* text_Score;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="MenuSettings")
	class UStackBox* st_MenuList;
	UPROPERTY(EditDefaultsOnly, Category="MenuSettings")
	TSubclassOf<class UEO_Menu> cucumberSushiMenu;
	UPROPERTY(EditDefaultsOnly,Category="MenuSettings")
	TSubclassOf<class UEO_Menu> fishSushiMenu;
	UPROPERTY(EditDefaultsOnly, Category="MenuSettings")
	TSubclassOf<class UEO_Menu> octopusSushiMenu;

private:
	UPROPERTY()
	class UEO_Menu* menuSlot;

	UPROPERTY()
	TArray<class UEO_Menu*> cucumberArr;
	UPROPERTY()
	TArray<class UEO_Menu*> fishArr;
	UPROPERTY()
	TArray<class UEO_Menu*> octopusArr;

	UPROPERTY()
	int menuCount = 0;
	UPROPERTY()
	int score = 0;

	UPROPERTY()
	float curTime = 0;
	UPROPERTY()
	float limitTime = 240;
	UPROPERTY()
	float menuCurTime = 0;
	UPROPERTY()
	float menuCoolTime = 2;

private:
	UFUNCTION()
	void SetTimerUI();
	UFUNCTION()
	void SpawnMenu(int randomNum);

public:
	UFUNCTION()
	void SubmitMenu(FName foodTag);
	UFUNCTION()
	void AddScore();
};
