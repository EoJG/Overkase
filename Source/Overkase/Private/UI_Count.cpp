// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Count.h"

void UUI_Count::GetMin()
{
	// �ð��� ������ �а��� �پ��� �ϰ� �ʹ�.
	// �ʿ�Ӽ� : currentTime, MinTime, SecTime
	
	// �ð��� �������ϱ�
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= 60 )
	{
		//�а��� �پ��� �ϰ� �ʹ�.
		if (--MinTime >= 0)
		{
			MinTime = MinTime - 1;
			CurrentTime = 0;
		}
	}
	
	
	// ���� �پ���.



}

void UUI_Count::GetSec()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= 60)
	{
		//�ʰ��� �پ��� �ϰ� �ʹ�.
		if (--SecTime >= 0)
		{
			SecTime = SecTime - 1;
			CurrentTime = 0;
		}
	}
}
