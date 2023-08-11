// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Count.h"
#include "Components/TextBlock.h"
#include <UMG/Public/Components/ProgressBar.h>



void UUI_Count::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CurrentTime -= InDeltaTime;
	
	// float�� ������ int ���������� ��ȯ
	Timer_MinCount->SetText(FText::AsNumber(int(GetMinutes())));
	Timer_SecCount->SetText(FText::AsNumber(int(GetSeconds())));
	
	
	timegage(InDeltaTime);
}


float UUI_Count::GetMinutes()
{
	// �ð��� ������ �а��� �پ��� �ϰ� �ʹ�.
	// �ʿ�Ӽ� : currentTime, MinTime, SecTime

	// �ð��� �������ϱ�
	/*CurrentTime -= seconds;*/
	if (CurrentTime <= 0)
	{
		//�а��� �پ��� �ϰ� �ʹ�.
		if (MinTime >= 0)
		{
			MinTime = MinTime - 1;
		}
	}
	return MinTime;


}

float UUI_Count::GetSeconds()
{
	// 59�ʰ� ������ Ŀ��ƮŸ���� 59�� ���µǰ� �ٽ� �ʰ��� -1�� �������� �ʹ�.
	
	if (CurrentTime <= 0)
	{
		CurrentTime = 59.9f;
	}

	return CurrentTime;

}

void UUI_Count::timegage(float value)
{
	//�ð��� �پ��� ��ŭ �������� �����ϰԲ� �ϰ� �ʹ�.
	//�ʿ�Ӽ�
	
	
	Timergage->SetPercent(ProgBar-value);
	
	

}

//
//void UUI_Count::GetMin(float seconds)
//{
//	// �ð��� ������ �а��� �پ��� �ϰ� �ʹ�.
//	// �ʿ�Ӽ� : currentTime, MinTime, SecTime
//	
//	// �ð��� �������ϱ�
//	CurrentTime -= seconds;
//	if (CurrentTime <= 0 )
//	{
//		//�а��� �پ��� �ϰ� �ʹ�.
//		if (MinTime >= 0)
//		{
//			MinTime = MinTime - 1;
//		}
//	}
//
//}
//
//void UUI_Count::GetSec(float seconds)
//{
//	// 59�ʰ� ������ Ŀ��ƮŸ���� 59�� ���µǰ� �ٽ� �ʰ��� -1�� �������� �ʹ�.
//	CurrentTime -= seconds;
//	if (CurrentTime <= 0)
//	{
//		CurrentTime = 59;
//	}
//}
