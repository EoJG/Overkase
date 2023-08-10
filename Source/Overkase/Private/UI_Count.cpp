// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Count.h"

void UUI_Count::GetMin()
{
	// 시간이 지나면 분값이 줄어들게 하고 싶다.
	// 필요속성 : currentTime, MinTime, SecTime
	
	// 시간이 지났으니까
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= 60 )
	{
		//분값이 줄어들게 하고 싶다.
		if (--MinTime >= 0)
		{
			MinTime = MinTime - 1;
			CurrentTime = 0;
		}
	}
	
	
	// 분이 줄어든다.



}

void UUI_Count::GetSec()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= 60)
	{
		//초값이 줄어들게 하고 싶다.
		if (--SecTime >= 0)
		{
			SecTime = SecTime - 1;
			CurrentTime = 0;
		}
	}
}
