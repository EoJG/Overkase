// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Menu.h"

void UEO_Menu::NativeConstruct()
{
	Super::NativeConstruct();

	curTime = coolTime;
}

void UEO_Menu::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);

	curTime -= DeltaTime;
	BindPercent();
	TimeOver();
}

void UEO_Menu::BindPercent()
{
	float percent = curTime / coolTime;

	progress_Timer->SetPercent(percent);
	
	if (percent >= 0.5f)
	{
		progress_Timer->SetFillColorAndOpacity(FColor(((1 - percent) * 2) * 255, 255, 0, 255));
	}
	else
	{
		progress_Timer->SetFillColorAndOpacity(FColor(255, (percent * 2) * 255, 0, 255));
	}
}

void UEO_Menu::TimeOver()
{
	
}

