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

	// ������ ���� ����
	// 1. Ÿ�̸� ī��Ʈ (��) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_MinCount;
	
	// 2. Ÿ�̸� ī��Ʈ (��) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* Timer_SecCount;

	// 3. Ÿ�̸� ī��Ʈ (:) - ���
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* edit_TimerCount;

	// 4. Ÿ�̸� ���α׷�����
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UProgressBar* Timergage;


	// 6. �ֹ�ǥ 1
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission1;
	
	// 7. �ֹ�ǥ 2
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission2;

	// 8. �ֹ�ǥ 3
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission3;

	// 9. �ֹ�ǥ 4
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission4;	
	
	// 10. �ֹ�ǥ 5
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* Mission5;

//====================================================================================

	// Ÿ�̸� �����ϱ�

	// ƽ ����� �Լ�
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	// �а��� 3������ ����
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

	// Ÿ�̸� UI ���ε��� ���� �Լ�
	float GetMinutes();
	float GetSeconds();


	//void GetMin(float seconds);
	//void GetSec(float seconds);
	// float ������ �Լ��� �����ϸ� ��ȯ���� float�ε�

//========================================================================================
	
	//Ÿ�̸� ������ UI�����

	UPROPERTY(BlueprintReadWrite, Category = ProgBar)
	float ProgBar = 0;


	// Ÿ�̸Ӱ����� UI �Լ�
	void timegage(float value);

	
	//UPROPERTY(BlueprintReadWrite, Category = secondTime)
	
//========================================================================================

	// �ֹ�ǥ �̼ǻ����ϱ�

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
