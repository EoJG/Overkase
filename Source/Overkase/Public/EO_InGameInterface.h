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
	class UWidgetSwitcher* ws_InGameSwitcher; 
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UTextBlock* text_Minute;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UTextBlock* text_Second;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="TimerSettings")
	class UProgressBar* progress_Timer;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category="ScoreSettings")
	class UTextBlock* text_Score;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="ScoreSettings")
	class UTextBlock* text_typingText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = "WidgetAnimation")
	class UWidgetAnimation* fadeInAnim;
	UPROPERTY(VisibleAnywhere, meta = (BindWidgetAnim), Transient, Category = "WidgetAnimation")
	class UWidgetAnimation* fadeOutAnim;

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
	class AH_OverkaseCharacter* me;

	UPROPERTY()
	TArray<class UEO_Menu*> cucumberArr;
	UPROPERTY()
	TArray<class UEO_Menu*> fishArr;
	UPROPERTY()
	TArray<class UEO_Menu*> octopusArr;

	

	UPROPERTY()
	float limitTime = 240;

	UPROPERTY(Replicated)
	float menuCurTime = 1;

	UPROPERTY(Replicated)
	float menuCoolTime = 2;

public:
	UPROPERTY(EditAnywhere)
	int SetTime = 180;
	
	UPROPERTY()
	int score = 0;

	UPROPERTY(Replicated)
	float curTime = 0;

	UPROPERTY(Replicated)
	int menuCount = 0;

	UPROPERTY(VisibleAnywhere)
	float startTime = 0;
	UPROPERTY(VisibleAnywhere)
	bool writing = false;
	UPROPERTY(VisibleAnywhere)
	FString strWriteText;
	UPROPERTY(EditDefaultsOnly)
	float charsPerSecond = 1;
	UPROPERTY(VisibleAnywhere)
	int charToDisplay = 0;

private:
	UFUNCTION()
	void SetTimerUI();


public:
	UFUNCTION(Server, Reliable)
	void ServerSpawnMenu();


	void AddScore();
	UFUNCTION()
	void SpawnMenu(int random);
	UFUNCTION()
	void SubmitMenu(FName foodTag);
	UFUNCTION(Server, Reliable)
	void ServerAddScore();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAddScore();
	UFUNCTION()
	void SetTimer(float settingTime);

	UFUNCTION(Server, Reliable)
	void ServerSubmitMenu(FName foodTag);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSubmitMenu(FName foodTag);
	
	UFUNCTION(Server, Reliable)
	void ServerTestFunc();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastTestFunc();

	UFUNCTION()
	void TestScore();

	UFUNCTION()
	void SetWriteText(FString setText);
	UFUNCTION()
	void WrtingText();

	UFUNCTION()
	void PlayFadeInAnim();
	UFUNCTION()
	void PlayFadeOutAnim();
		
private:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	int randomNum = 0;
};
