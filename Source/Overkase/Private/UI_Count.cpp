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

	ProgBar = CurrentTime / MaxTime;
	
	timegage(InDeltaTime);
}


float UUI_Count::GetMinutes()
{
	// �ð��� ������ �а��� �پ��� �ϰ� �ʹ�.
	// �ʿ�Ӽ� : currentTime, MinTime, SecTime

	// �ð��� �������ϱ�
	/*CurrentTime -= seconds;*/
	// CurT�� ���̳ʽ��� �Ǹ� �ȵǴϱ� 0���� Ŭ�������� ī��Ʈ ����
	if (CurrentTime > 0)
	{
		//�а��� �پ��� �ϰ� �ʹ�.
		MinTime = CurrentTime / 60;
	}
	return MinTime;


}

float UUI_Count::GetSeconds()
{
	// 59�ʰ� ������ Ŀ��ƮŸ���� 59�� ���µǰ� �ٽ� �ʰ��� -1�� �������� �ʹ�.
	
	if (CurrentTime > 0)
	{
		// �Ǽ����� �����ϱ� ���� ��
		SecTime = FMath::Fmod(CurrentTime, 60);
		//SecTime = CurrentTime % 60;
	}

	return SecTime;

}

void UUI_Count::timegage(float value)
{
	//�ð��� �پ��� ��ŭ �������� �����ϰԲ� �ϰ� �ʹ�.
	//�ʿ�Ӽ�
	
	
	Timergage->SetPercent(ProgBar);
	
	

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
