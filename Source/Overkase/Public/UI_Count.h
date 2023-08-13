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

	// 위젯을 생성 선언
	// 1. 타이머 카운트 (분) - 경렬
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_MinCount;
	
	// 2. 타이머 카운트 (초) - 경렬
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_SecCount;

	// 3. 타이머 카운트 (:) - 경렬
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* edit_TimerCount;

	// 4. 타이머 프로그래스바
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UProgressBar* Timergage;


	// 6. 주문표 1
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission1;
	
	// 7. 주문표 2
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission2;

	// 8. 주문표 3
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission3;

	// 9. 주문표 4
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission4;	
	
	// 10. 주문표 5
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission5;

//====================================================================================

	// 타이머 셋팅하기

	// 틱 만들기 함수
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	// 분값은 3분으로 셋팅
	UPROPERTY(BlueprintReadWrite, Category = minuteTime)
	float MinTime = 03;

	// 
	UPROPERTY(BlueprintReadWrite, Category = secondTime)
	float SecTime = 0;

	// 
	UPROPERTY(BlueprintReadOnly)
	float CurrentTime = 210;

	UPROPERTY(BlueprintReadOnly)
	float MaxTime = 210;

	// 타이머 UI 바인딩을 위한 함수
	float GetMinutes();
	float GetSeconds();


	//void GetMin(float seconds);
	//void GetSec(float seconds);
	// float 형태의 함수를 선언하면 반환값은 float인데

//========================================================================================
	
	//타이머 게이지 UI만들기

	UPROPERTY(BlueprintReadWrite, Category = ProgBar)
	float ProgBar = 0;


	// 타이머게이지 UI 함수
	void timegage(float value);

	
	//UPROPERTY(BlueprintReadWrite, Category = secondTime)
	
//========================================================================================

	// 주문표 미션생성하기

//public:
//	UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
//	class AEO_Food* cucumberSushi;
//	
//	UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
//	class AEO_Food* octorSushi;
//
//	UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
//	class AEO_Food* Hamburger;
//
//	void Get_Mission();









};
