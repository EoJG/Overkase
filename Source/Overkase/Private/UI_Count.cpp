// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Count.h"
#include "Components/TextBlock.h"
#include <UMG/Public/Components/ProgressBar.h>



void UUI_Count::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CurrentTime -= InDeltaTime;
	
	// float인 변수를 int 정수형으로 변환
	Timer_MinCount->SetText(FText::AsNumber(int(GetMinutes())));
	Timer_SecCount->SetText(FText::AsNumber(int(GetSeconds())));
	
	
	timegage(InDeltaTime);
}


float UUI_Count::GetMinutes()
{
	// 시간이 지나면 분값이 줄어들게 하고 싶다.
	// 필요속성 : currentTime, MinTime, SecTime

	// 시간이 지났으니까
	/*CurrentTime -= seconds;*/
	if (CurrentTime <= 0)
	{
		//분값이 줄어들게 하고 싶다.
		if (MinTime >= 0)
		{
			MinTime = MinTime - 1;
		}
	}
	return MinTime;


}

float UUI_Count::GetSeconds()
{
	// 59초가 지나면 커런트타임이 59로 리셋되고 다시 초값이 -1씩 떨어지고 싶다.
	
	if (CurrentTime <= 0)
	{
		CurrentTime = 59.9f;
	}

	return CurrentTime;

}

void UUI_Count::timegage(float value)
{
	//시간이 줄어드는 만큼 게이지가 감소하게끔 하고 싶다.
	//필요속성
	
	
	Timergage->SetPercent(ProgBar-value);
	
	

}

//
//void UUI_Count::GetMin(float seconds)
//{
//	// 시간이 지나면 분값이 줄어들게 하고 싶다.
//	// 필요속성 : currentTime, MinTime, SecTime
//	
//	// 시간이 지났으니까
//	CurrentTime -= seconds;
//	if (CurrentTime <= 0 )
//	{
//		//분값이 줄어들게 하고 싶다.
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
//	// 59초가 지나면 커런트타임이 59로 리셋되고 다시 초값이 -1씩 떨어지고 싶다.
//	CurrentTime -= seconds;
//	if (CurrentTime <= 0)
//	{
//		CurrentTime = 59;
//	}
//}
